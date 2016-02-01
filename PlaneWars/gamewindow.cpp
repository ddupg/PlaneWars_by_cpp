#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(int level, int playerNum, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

	creatMenu();

	this->setWindowTitle("PlaneWars");

	// 设置背景音乐
	bgsound = new QSound("Resources/sounds/bgmusic.wav");
	bgsound->setLoops(QSound::Infinite);
	bgsound->play();

	// 设置关卡难度
	chapter = new Chapter(level);
	// 设置玩家数量，只允许1~2个玩家
	this->playerNum = playerNum;
	this->setPlayer();
	boss = NULL;
	bossDead = false;

	// 设置背景图片
	bgimg = chapter->getBackGroundPixmap();
	bgimg = bgimg.scaled(GAME_WINDOW_WIDTH,
		bgimg.height() * GAME_WINDOW_WIDTH / bgimg.width() + 1, Qt::KeepAspectRatio);

	// 设置窗口大小为默认大小
	this->resize(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);

	// 设置窗口出现在屏幕中央
	QDesktopWidget *desktop = QApplication::desktop();
	this->move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);

	// 定时器设置
	gameTime = new QTime();
	gameTime->start();

	updateTimer = new QTimer();
	updateTimer->start(WINDOW_UPDATE_INTERVAL);

	/******************** 建立计时器的信号与槽连接 *********************/
	// 定时更新
	connect(updateTimer, SIGNAL(timeout()), updateTimer, SLOT(start(WINDOW_UPDATE_INTERVAL)));
	connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));

	// 关卡更新
	chapterTimer = new QTimer();
	chapterTimer->start(CHAPTER_TIME);
	connect(chapterTimer, SIGNAL(timeout()), this, SLOT(chapterUpgrade()));

	planesList.clear();
	bulletList.clear();
	playerBulletList.clear();
	bombList.clear();
	supplyList.clear();
}

GameWindow::~GameWindow()
{
    delete ui;
	delete chapter;
	if (bgsound != NULL){
		delete bgsound;
	}
	for (auto x : planesList){
		delete x;
	}
	if (gameTime != NULL){
		delete gameTime;
	}
	if (updateTimer != NULL){
		delete updateTimer;
	}
	// 删除飞机列表
	for (; !planesList.empty(); planesList.pop_front()){
		EnemyPlane* plane = *planesList.begin();
		delete plane;
		plane = NULL;
	}
	// 删除子弹列表
	for (; !bulletList.empty(); bulletList.pop_front()){
		Bullet* bullet = *bulletList.begin();
		delete bullet;
		bullet = NULL;
	}
	for (int i = 0; i < 2; i++){
		if (player[i] != NULL){
			delete player[i];
			player[i] = NULL;
		}
	}
}

void GameWindow::paintEvent(QPaintEvent * event){
	
	checkUpdate();

	/******************** 各种绘图 ***********************/

	QPainter * painter = new QPainter(this);

	long long runTime = gameTime->elapsed() / 10 % (bgimg.height());

	// 重绘背景
	bgimg = bgimg.scaled(this->width(), 
		(int)(1.0 * bgimg.height() * this->width() / bgimg.width()), Qt::KeepAspectRatio);

	painter->drawPixmap(0, runTime - bgimg.height(), bgimg.width(), bgimg.height(), bgimg);
	painter->drawPixmap(0, runTime, bgimg.width(), bgimg.height(), bgimg);
	painter->drawPixmap(0, runTime + bgimg.height(), bgimg.width(), bgimg.height(), bgimg);


	// 绘制飞行物
	for (auto flyer : flyerList){
		flyer->Paint(painter, this->geometry());
	}

	// 绘制爆炸
	for (QList<Bomb*>::iterator it = bombList.begin(), curIt; it != bombList.end();){
		Bomb * bomb = *(curIt = it++);
		if (!bomb->Paint(painter)){
			delete bomb;
			bomb = NULL;
			it = bombList.erase(curIt);
		}
	}

	// 绘制玩家飞机
	for (int i = 0; i<2; i++){
		if (player[i] != NULL && player[i]->getBlood() > 0){
			player[i]->Paint(painter, this->geometry());
		}
	}

	// Chapter 图

	int x = CHAPTER_TIME - chapterTimer->remainingTime();
	if (x <= 2000){
		QPixmap chapterImg;
		chapterImg.load("Resources/image/chapter"+IntToQString(chapter->getChapterLevel())+".png");
		chapterImg = chapterImg.scaled(this->width(), 1.0 * chapterImg.height() * this->width() / chapterImg.height(), Qt::KeepAspectRatio);
		painter->drawPixmap(0, 0, chapterImg);
	}

	delete painter;

	showPlayerMessage();
}

// 关卡升级，难度升级，返回false说明通关，返回true说明升级成功
void GameWindow::chapterUpgrade(){
	if (chapter->getChapterLevel() == CHAPTER_NUM){

		boss = new Boss(QPoint(width() / 2, height() / 3), "Resources/image/boss.png", PLANE_DIR_UP);
		boss->setSpeedVector(QPoint(-PLANE_SPEED / 2, -PLANE_SPEED / 2));
		bossDead = false;

		chapterTimer->stop();

		setWindowTitle("woca");

		return;
	}
	int level = chapter->getChapterLevel();
	delete chapter;
	chapter = new Chapter(level + 1);
	bgimg = chapter->getBackGroundPixmap();
}

void GameWindow::setPlayer(){

	for (int i = 0; i<2; i++){
		player[i] = NULL;
		playerAttackFlag[i] = NULL;
	}

	if (playerNum == 1){
		// 玩家1飞机
		player[0] = new PlayerPlane(QPoint((this->width() - PLAYER_PLANE_WIDTH) / 2, this->height() / 3 * 2), 
			"Resources/image/playerplane1.png", 0, PLAYER_BLOOD);
	}
	else{
		// 玩家1飞机
		player[0] = new PlayerPlane(QPoint(this->width() / 4 - PLAYER_PLANE_WIDTH / 2, this->height() / 3 * 2),
			"Resources/image/playerplane1.png", 0, PLAYER_BLOOD);
		// 玩家2飞机
		player[1] = new PlayerPlane(QPoint(this->width() / 4 * 3 - PLAYER_PLANE_WIDTH / 2, this->height() / 3 * 2),
			"Resources/image/playerplane1.png", 0, PLAYER_BLOOD);
	}
}

// 键盘按下事件
void GameWindow::keyPressEvent(QKeyEvent * event){

	// 玩家1速度设置
	if (player[0] != NULL){
		QPoint speed1 = player[0]->getSpeedVector();
		if (event->key() == Qt::Key_A){ // 左
			speed1.setX(speed1.x() - PLAYER_PLANE_SPEED);
		}
	
		if (event->key() == Qt::Key_W){ // 上
			speed1.setY(speed1.y() - PLAYER_PLANE_SPEED);
		}
		if (event->key() == Qt::Key_D){ // 右
			speed1.setX(speed1.x() + PLAYER_PLANE_SPEED);
		}
		if (event->key() == Qt::Key_S){ // 下
			speed1.setY(speed1.y() + PLAYER_PLANE_SPEED);
		}
		player[0]->setSpeedVector(speed1);

		// 玩家1攻击设置
		if (event->key() == Qt::Key_Space){
			playerAttackFlag[0] = true;
		}
		if (event->key() == Qt::Key_Control){
			if (planesList.size()){
				player[0]->getMissile(missileList, planesList.at(getRandom(0, planesList.size()-1)));
			}
			else{
				player[0]->getMissile(missileList, NULL);
			}
		}
	}

	if (player[1] != NULL){
		// 玩家2速度设置
		QPoint speed2 = player[1]->getSpeedVector();
		if (event->key() == Qt::Key_Left){ // 左
			speed2.setX(speed2.x() - PLAYER_PLANE_SPEED);
		}
		if (event->key() == Qt::Key_Up){ // 上
			speed2.setY(speed2.y() - PLAYER_PLANE_SPEED);
		}
		if (event->key() == Qt::Key_Right){ // 右
			speed2.setX(speed2.x() + PLAYER_PLANE_SPEED);
		}
		if (event->key() == Qt::Key_Down){ // 下
			speed2.setY(speed2.y() + PLAYER_PLANE_SPEED);
		}
		player[1]->setSpeedVector(speed2);
		// 玩家2攻击设置
		if (event->key() == Qt::Key_0){
			playerAttackFlag[1] = true;
		}
		if (event->key() == Qt::Key_Enter){
			if (planesList.size()){
				player[1]->getMissile(missileList, planesList.at(getRandom(0, planesList.size() - 1)));
			}
			else{
				player[1]->getMissile(missileList, NULL);
			}
		}
	}
}

// 键盘松手事件
void GameWindow::keyReleaseEvent(QKeyEvent * event){

	// 玩家1速度设置
	if (player[0] != NULL){
		QPoint speed = player[0]->getSpeedVector();
		if (event->key() == Qt::Key_A){ // 左
			speed.setX(speed.x() + PLAYER_PLANE_SPEED);
		}
		if (event->key() == Qt::Key_W){ // 上
			speed.setY(speed.y() + PLAYER_PLANE_SPEED);
		}
		if (event->key() == Qt::Key_D){ // 右
			speed.setX(speed.x() - PLAYER_PLANE_SPEED);
		}
		if (event->key() == Qt::Key_S){ // 下
			speed.setY(speed.y() - PLAYER_PLANE_SPEED);
		}
		player[0]->setSpeedVector(speed);
		// 玩家1攻击设置
		if (event->key() == Qt::Key_Space){
			playerAttackFlag[0] = false;
		}
	}

	if (player[1] != NULL){
		QPoint speed = player[1]->getSpeedVector();
		// 左
		if (event->key() == Qt::Key_Left){
			speed.setX(speed.x() + PLAYER_PLANE_SPEED);
		}
		// 上
		if (event->key() == Qt::Key_Up){
			speed.setY(speed.y() + PLAYER_PLANE_SPEED);
		}
		// 右
		if (event->key() == Qt::Key_Right){
			speed.setX(speed.x() - PLAYER_PLANE_SPEED);
		}
		// 下
		if (event->key() == Qt::Key_Down){
			speed.setY(speed.y() - PLAYER_PLANE_SPEED);
		}
		player[1]->setSpeedVector(speed);
		// 玩家2攻击设置
		if (event->key() == Qt::Key_0){
			playerAttackFlag[1] = false;
		}
	}
}

void GameWindow::checkUpdate(){

	/************************ 检测 游戏是否结束****************************/
	// 游戏结束检测
	for (int i = 0; i < 2; i++){
		if (player[i] != NULL && player[i]->getBlood() <= 0){
			delete player[i];
			player[i] = NULL;
		}
	}

	if (player[0] == NULL && player[1] == NULL){
		//游戏结束
		updateTimer->stop();
		chapterTimer->stop();

		GameOver g(GAMEOVER, this);
		g.exec();

		exit(0);
	}

	// 添加Boss
	if (boss != NULL && boss->getBlood() <= 0){
		//this->hide();
		GameOver g(YOUAREWIN);
		g.exec();
		delete boss;
		boss = NULL;
		bossDead = true;
		exit(0);
	}
	if (boss != NULL){
		boss->getBullet(bulletList);
	}

	// 添加敌机
	if (chapter->getPlaneAppearProbability()){
		chapter->getEnemyPlane(planesList, this->rect());
	}
	// 添加客机
	chapter->getPassengerPlane(passengerPlaneList, this->rect());

	// 随机选择飞机添加子弹
	if (chapter->getAttackProbability() && planesList.size() > 0){
		EnemyPlane * plane = planesList.at(getRandom(0, planesList.size() - 1));
		plane->getBullet(bulletList);
	}

	// 添加玩家飞机子弹，用updateCount控制，防止子弹过密
	(++updateCount) %= 3;
	for (int i = 0; i<2; i++){
		if (player[i] != NULL && playerAttackFlag[i] && updateCount == 0){
			player[i]->getBullet(playerBulletList);
		}
	}

	//********************** 处理碰撞 **************************//
	for (int i = 0; i<2; i++){
		if (player[i] != NULL){
			// 检测玩家与敌机子弹
			for (QList<Bullet*>::iterator it = bulletList.begin(), curIt; it != bulletList.end();){
				Bullet * bullet = *(curIt = it++);
				if (player[i]->isCrashed(*bullet)){
					player[i]->getAttacked(bullet->getAttackPower());
					delete bullet;
					bullet = NULL;
					it = bulletList.erase(curIt);
				}
			}
			// 检测玩家与敌机
			for (QList<EnemyPlane*>::iterator it = planesList.begin(), curIt; it != planesList.end();){
				EnemyPlane * plane = *(curIt = it++);
				if (player[i]->isCrashed(*plane)){
					player[i]->getAttacked(plane->getAttackPower());
					bombList.push_back(new Bomb(plane->getCurPostion()));
					delete plane;
					plane = NULL;
					it = planesList.erase(curIt);
				}
			}
			// 检测玩家与补寄
			for (QList<Supply*>::iterator it = supplyList.begin(), curIt; it != supplyList.end();){
				Supply* supply = *(curIt = it++);
				if (player[i]->isCrashed(*supply)){
					player[i]->getSupply(supply->getSupplyType());
					delete supply;
					supply = NULL;
					it = supplyList.erase(curIt);
				}
			}
			// 检测玩家与乘客
			for (QList<Bullet*>::iterator it = passengerList.begin(), curIt; it != passengerList.end();){
				Bullet* passenger = *(curIt = it++);
				if (player[i]->isCrashed(*passenger)){
					PlayerPlane::addScore(10);
					delete passenger;
					passenger = NULL;
					it = passengerList.erase(curIt);
				}
			}
		}
	}

	//检测敌机与玩家子弹
	for (QList<EnemyPlane*>::iterator planeIt = planesList.begin(), planeCurIt; planeIt != planesList.end(); ){
		EnemyPlane * plane = *(planeCurIt = planeIt++);

		for (QList<Bullet*>::iterator bulletIt = playerBulletList.begin(), bulletCurIt; bulletIt != playerBulletList.end();){
			Bullet * bullet = *(bulletCurIt = bulletIt++);
			if (plane->isCrashed(*bullet)){
				plane->getAttacked(bullet->getAttackPower());

				bombList.push_back(new Bomb(plane->getCurPostion()));

				// 添加补寄
				if (chapter->getSupplyProbability()){
					chapter->getSupply(supplyList, plane->getCurPostion());
				}

				delete plane;
				plane = NULL;
				planeIt = planesList.erase(planeCurIt);

				delete bullet;
				bullet = NULL;
				bulletIt = playerBulletList.erase(bulletCurIt);

				// 普通敌机被击毁玩家+5
				PlayerPlane::addScore(5);

				break;
			}
		}
	}

	// 检测玩家子弹与客机
	for (QList<PassengerPlane*>::iterator planeIt = passengerPlaneList.begin(), planeCurIt; planeIt != passengerPlaneList.end();){
		PassengerPlane * plane = *(planeCurIt = planeIt++);
		for (QList<Bullet*>::iterator bulletIt = playerBulletList.begin(), bulletCurIt; bulletIt != playerBulletList.end();){
			Bullet * bullet = *(bulletCurIt = bulletIt++);
			if (plane->isCrashed(*bullet)){
				plane->getBullet(passengerList);
				plane->getAttacked(bullet->getAttackPower());
				if (plane->getBlood() <= 0){

					// 添加乘客
					plane->getBullet(passengerList);

					delete plane;
					plane = NULL;
					planeIt = passengerPlaneList.erase(planeCurIt);
					// 玩家减分
					PlayerPlane::addScore(-20);
				}

				delete bullet;
				bullet = NULL;
				bulletIt = playerBulletList.erase(bulletCurIt);

				break;
			}
		}
	}

	// 检测敌机与导弹
	for (QList<EnemyPlane*>::iterator planeIt = planesList.begin(), planeCurIt; planeIt != planesList.end();){
		EnemyPlane * plane = *(planeCurIt = planeIt++);

		for (QList<Missile*>::iterator missileIt = missileList.begin(), missileCurIt; missileIt != missileList.end();){
			Missile * missile = *(missileCurIt = missileIt++);
			if (plane->isCrashed(*missile)){
				plane->getAttacked(missile->getAttackPower());

				bombList.push_back(new Bomb(plane->getCurPostion()));

				// 添加补寄
				if (chapter->getSupplyProbability()){
					chapter->getSupply(supplyList, plane->getCurPostion());
				}
				else{
					qDebug() << "*********************************";
				}

				delete plane;
				plane = NULL;
				planeIt = planesList.erase(planeCurIt);

				delete missile;
				missile = NULL;
				missileIt = missileList.erase(missileCurIt);

				// 打掉普通敌机+5
				PlayerPlane::addScore(5);

				break;
			}
		}
	}
	if (boss != NULL){
		for (QList<Bullet*>::iterator it = playerBulletList.begin(), curIt; it != playerBulletList.end();){
			Bullet * bullet = *(curIt = it++);
			if (boss->isCrashed(*bullet)){
				boss->getAttack(bullet->getAttackPower());
				delete bullet;
				bullet = NULL;
				it = playerBulletList.erase(curIt);
			}
		}
		for (QList<Missile*>::iterator it = missileList.begin(), curIt; it != missileList.end();){
			Bullet * missile = *(curIt = it++);
			if (boss->isCrashed(*missile)){
				boss->getAttack(missile->getAttackPower());
				delete missile;
				missile = NULL;
				it = missileList.erase(curIt);
			}
		}
	}

	/************************** 所有飞行物移动 *************************************/

	for (int i = 0; i<2; i++){
		if (player[i] != NULL){
			player[i]->move(this->geometry());
		}
	}

	for (auto x : playerBulletList){
		x->move(this->geometry());
	}
	for (auto x : missileList){
		if (planesList.size()){
			x->moveto(planesList.at(0)->getCurPostion());
			x->move();
		}
		else{
			x->move();
		}
	}
	for (auto x : bulletList){
		x->move(this->geometry());
	}
	for (auto x : planesList){
		x->move(this->geometry());
	}
	for (auto x : supplyList){
		x->move(this->geometry());
	}

	for (auto x : passengerList){
		x->move(this->geometry());
	}
	for (auto x : passengerPlaneList){
		x->move(this->geometry());
	}
	if (boss != NULL){
		boss->move(this->geometry());
	}

	/************************** 判断越界 ***************************/

	flyerList.clear();
	if (boss != NULL){
		flyerList.append(boss);
	}
	// 玩家子弹
	for (QList<Bullet*>::iterator it = playerBulletList.begin(), curIt; it != playerBulletList.end();){
		Bullet* bullet = *(curIt = it++);
		bool paintFlag = RectangleIntersection(
			QRect(bullet->getCurPostion() - QPoint(bullet->width() / 2, bullet->height() / 2), 
				bullet->getCurPostion() + QPoint(bullet->width() / 2, bullet->height() / 2)),
			QRect(QPoint(0, 0), QPoint(this->width(), this->height())));
		if (paintFlag){
			flyerList.append(bullet);
		}
		else{
			delete bullet;
			bullet = NULL;
			it = playerBulletList.erase(curIt);
		}
	}
	// 导弹
	for (QList<Missile*>::iterator it = missileList.begin(), curIt; it != missileList.end();){
		Missile * bullet = *(curIt = it++);
		bool paintFlag = RectangleIntersection(
			QRect(bullet->getCurPostion() - QPoint(bullet->width() / 2, bullet->height() / 2),
			bullet->getCurPostion() + QPoint(bullet->width() / 2, bullet->height() / 2)),
			QRect(QPoint(0, 0), QPoint(this->width(), this->height())));
		if (paintFlag){
			flyerList.append(bullet);
		}
		else{
			delete bullet;
			bullet = NULL;
			it = missileList.erase(curIt);
		}
	}

	// 敌机子弹
	for (QList<Bullet*>::iterator it = bulletList.begin(), curIt; it != bulletList.end();){
		Bullet* bullet = *(curIt = it++);
		bool paintFlag = RectangleIntersection(
			QRect(bullet->getCurPostion() - QPoint(bullet->width() / 2, bullet->height() / 2), 
				bullet->getCurPostion() + QPoint(bullet->width() / 2, bullet->height() / 2)),
			QRect(QPoint(0, 0), QPoint(this->width(), this->height())));

		if (paintFlag){
			flyerList.append(bullet);
		}
		else{
			delete bullet;
			bullet = NULL;
			it = bulletList.erase(curIt);
		}
	}

	
	// 敌机
	for (QList<EnemyPlane*>::iterator it = planesList.begin(), curIt; it != planesList.end();){
		EnemyPlane* plane = *(curIt = it++);
		bool paintFlag = RectangleIntersection(
			QRect(plane->getCurPostion() - QPoint(plane->width() / 2, plane->height() / 2), 
				plane->getCurPostion()+ QPoint(plane->width() / 2, plane->height() / 2)),
			QRect(QPoint(0, 0), QPoint(this->width(), this->height())))
			&& plane->getBlood() > 0;

		if (paintFlag){
			flyerList.append(plane);
		}
		else{
			delete plane;
			plane = NULL;
			it = planesList.erase(curIt);
		}
	}

	//补寄
	for (QList<Supply*>::iterator it = supplyList.begin(), curIt; it != supplyList.end();){
		Flyer * supply = *(curIt = it++);
		bool paintFlag = RectangleIntersection(
			QRect(supply->getCurPostion() - QPoint(supply->width() / 2, supply->height() / 2),
				supply->getCurPostion() + QPoint(supply->width() / 2, supply->height() / 2)),
			QRect(QPoint(0, 0), QPoint(this->width(), this->height())));

		if (paintFlag){
			flyerList.append(supply);
		}
		else{
			delete supply;
			supply = NULL;
			it = supplyList.erase(curIt);
		}
	}
	// 客机
	for (QList<PassengerPlane*>::iterator it = passengerPlaneList.begin(), curIt; it != passengerPlaneList.end();){
		PassengerPlane *plane = *(curIt = it++);
		bool paintFlag = RectangleIntersection(
			QRect(plane->getCurPostion() - QPoint(plane->width() / 2, plane->height() / 2),
			plane->getCurPostion() + QPoint(plane->width() / 2, plane->height() / 2)),
			QRect(QPoint(0, 0), QPoint(this->width(), this->height())));

		if (paintFlag){
			flyerList.append(plane);
		}
		else{
			delete plane;
			plane = NULL;
			it = passengerPlaneList.erase(curIt);
		}
	}
	for (QList<Bullet*>::iterator it = passengerList.begin(), curIt; it != passengerList.end();){
		Bullet *passenger = *(curIt = it++);
		bool paintFlag = RectangleIntersection(
			QRect(passenger->getCurPostion() - QPoint(passenger->width() / 2, passenger->height() / 2),
			passenger->getCurPostion() + QPoint(passenger->width() / 2, passenger->height() / 2)),
			QRect(QPoint(0, 0), QPoint(this->width(), this->height())));

		if (paintFlag){
			flyerList.append(passenger);
		}
		else{
			delete passenger;
			passenger = NULL;
			it = passengerList.erase(curIt);
		}
	}
}

void GameWindow::showPlayerMessage(){

	
	QPainter painter(this);
	QPen pen(Qt::black, 1, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
	QFont font = painter.font();
	font.setPixelSize(50);
	font.setBold(true);
	painter.setFont(font);
	painter.setPen(pen);

	if (player[0] != NULL){
		painter.drawRect(24, 34, 100, 15);
		QRect rect(24, 34, player[0]->getBlood(), 15);
		painter.fillRect(rect, QBrush(Qt::red, Qt::SolidPattern));
	}

	if (player[1] != NULL){
		painter.drawRect(24, 64, 100, 15);
		QRect rect(24, 64, player[1]->getBlood(), 15);
		painter.fillRect(rect, QBrush(Qt::green, Qt::SolidPattern));
	}

	painter.drawText(150, 64, IntToQString(PlayerPlane::getScore()));

	if (boss != NULL){
		painter.drawRect(24, 94, 200, 15);
		QRect rect(24, 94, boss->getBlood(), 15);
		painter.fillRect(rect, QBrush(Qt::black, Qt::SolidPattern));
	}

	painter.end();
}

void GameWindow::creatMenu(){
	menu = this->menuBar()->addMenu(tr("Game"));

	stopAction = new QAction("Stop", this);
	connect(stopAction, SIGNAL(triggered()), this, SLOT(stop()));
	connect(stopAction, SIGNAL(triggered()), this, SLOT(changeMenuEnabled()));
	menu->addAction(stopAction);

	restartAction = new QAction("Restart", this);
	restartAction->setEnabled(false);
	connect(restartAction, SIGNAL(triggered()), this, SLOT(restart()));
	connect(restartAction, SIGNAL(triggered()), this, SLOT(changeMenuEnabled()));
	menu->addAction(restartAction);

	menu->addSeparator();

	invincibleAction = new QAction("Invincible", this);
	connect(invincibleAction, SIGNAL(triggered()), this, SLOT(changeInvincible()));
	menu->addAction(invincibleAction);

	menu->addSeparator();

	adjustAction = new QAction("Adjust", this);
	connect(adjustAction, SIGNAL(triggered()), this, SLOT(adjust()));
	menu->addAction(adjustAction);
}

void GameWindow::stop(){
	runTime += gameTime->elapsed();
	updateTimer->stop();

	chapterRemainingTime = chapterTimer->remainingTime();
	chapterTimer->stop();
}

void GameWindow::restart(){
	gameTime->restart();
	updateTimer->start(WINDOW_UPDATE_INTERVAL);

	chapterTimer->start(chapterRemainingTime);
}

void GameWindow::changeMenuEnabled(){
	if (stopAction->isEnabled()){
		stopAction->setEnabled(false);
		restartAction->setEnabled(true);
	}
	else{
		stopAction->setEnabled(true);
		restartAction->setEnabled(false);
	}
}

long long GameWindow::getRunTime(){
	return gameTime->elapsed() + this->runTime;
}

void GameWindow::changeInvincible(){
	for (int i = 0; i < 2; i++){
		if (player[i] != NULL){
			player[i]->changeInvincible();
		}
	}
}

void GameWindow::adjust(){
	stop();

	Adjust a(chapter, this);
	a.exec();

	restart();
}

void GameWindow::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton) {
		QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId(), pos().x(), pos().y(), frameGeometry().width(), frameGeometry().height());
		QString fileName = QString("screenshot/") + IntToQString(getRunTime()) + ".png";
		qDebug() << fileName;
		pixmap.save(fileName);
	}
}
