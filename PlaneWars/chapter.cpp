#include "chapter.h"

Chapter::Chapter(int level = 1){
	this->chapterLevel = level;
	if (chapterLevel > 3 || chapterLevel < 1){
		return ;
	}

	// 设置敌机出现概率
	setBasicPlaneAppearProbability(50);

	// 设置敌机攻击频率
	setBasicAttackProbability(50);

	// 设置补寄出现概率
	setBasicSupplyProbability(50);

	// 设置背景图片
	bgmap.load(QString("Resources/image/gamebg") + IntToQString(chapterLevel) + ".bmp");
}

Chapter::~Chapter()
{
}

int Chapter::getChapterLevel(){
	return this->chapterLevel;
}

bool Chapter::getPlaneAppearProbability(){
	return rand() % 100000000 / 100000000.0 < PlaneAppearProbability;
}

bool Chapter::getAttackProbability(){
	return rand() % 100000000 / 100000000.0 < AttackProbability;
}

bool Chapter::getSupplyProbability(){
	return rand() % 1000000 / 1000000.0 < SupplyProbability;
}

QPixmap Chapter::getBackGroundPixmap(){
	return bgmap;
}

void Chapter::getEnemyPlane(QList<EnemyPlane*>& list, QRect rect){
	if (rand() % 1000 / 1000.0 < 0.1 * chapterLevel){
		QString imgPath = QString("Resources/image/enemyplane") + IntToQString(getRandom(1, 10)) + ".png";
		EnemyPlane * plane = new EnemyPlane(QPoint(getRandom(0, rect.width()), rect.height()), imgPath, PLANE_DIR_UP, 1);
		plane->setAttackPower(PLANE_ATTACK + chapterLevel);
		list.append(plane);
	}
	else{
		QString imgPath = QString("Resources/image/enemyplane") + IntToQString(getRandom(1, 10)) + ".png";
		EnemyPlane * plane = new EnemyPlane(QPoint(getRandom(0, rect.width()), 0), imgPath, PLANE_DIR_DOWN, 1);
		plane->setAttackPower(PLANE_ATTACK + chapterLevel);
		plane->Rotate180();
		list.append(plane);
	}
}

void Chapter::getSupply(QList<Supply*>& list, QPoint pos){

	if (rand() % 1000 / 1000.0 < 0.7){
		QString imgPath = QString("Resources/image/bloodsupply.png");
		Supply* supply = new Supply(BLOOD_SUPPLY_TYPE, pos, imgPath, PLANE_DIR_UP);
		supply->setSpeedVector(QPoint(0, PLANE_SPEED));
		list.append(supply);
	}
	else{
		QString imgPath = QString("Resources/image/attacksupply.png");
		Supply* supply = new Supply(ATTACK_SUPPLY_TYPE, pos, imgPath, PLANE_DIR_UP);
		supply->setSpeedVector(QPoint(0, PLANE_SPEED));
		list.append(supply);
	}
}

// 敌机出现频率
void Chapter::setBasicPlaneAppearProbability(int x){

	basicPlaneAppearProbability = x / 100.0 * 0.00003;
	PlaneAppearProbability = basicPlaneAppearProbability * chapterLevel;
}
int Chapter::getBasicPlaneAppearProbability(){
	return (int)(basicPlaneAppearProbability / 0.00003 * 100);
}

// 攻击频率
void Chapter::setBasicAttackProbability(int x){
	basicAttackProbability = x / 100.0;
	AttackProbability = basicAttackProbability * PlaneAppearProbability * 10;
}
int Chapter::getBasicAttackProbability(){
	return (int)(basicAttackProbability * 100);
}

// 补寄掉落频率
void Chapter::setBasicSupplyProbability(int x){
	basicSupplyProbability = x / 5000.0;
	SupplyProbability = basicSupplyProbability;
}
int Chapter::getBasicSupplyProbability(){
	return (int)(basicSupplyProbability * 5000);
}

void Chapter::getPassengerPlane(QList<PassengerPlane*>& list, QRect rect){
	if (rand() % 10000 / 10000.0 < 0.003){
		PassengerPlane *plane = new PassengerPlane(QPoint(getRandom(0, rect.width()), 0), 
			"Resources/image/passengerplane.png", PLANE_DIR_DOWN, PASSENGER_PLANE_BLOOD);
		plane->Rotate180();
		list.append(plane);
	}
}