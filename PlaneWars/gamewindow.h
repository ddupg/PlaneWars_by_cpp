#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "header.h"
#include "chapter.h"
#include "bomb.h"
#include "missile.h"
#include "adjust.h"
#include "gameover.h"
#include "boss.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(int level = 1, int playerNum = 2, QWidget *parent = 0);
    ~GameWindow();
	void paintEvent(QPaintEvent * event);
	void keyPressEvent(QKeyEvent * event);
	void keyReleaseEvent(QKeyEvent * event);
	void mousePressEvent(QMouseEvent * event);

	long long getRunTime();


private:
    Ui::GameWindow *ui;
	// 更新计时器
	QTimer * updateTimer;
	int updateCount = 0;

	// 关卡计时器
	QTimer * chapterTimer;
	int chapterRemainingTime;

	// 游戏计时器
	QTime *gameTime;
	long long runTime = 0;
	// 关卡难度
	Chapter *chapter;
	// 背景图
	QPixmap bgimg;

	// 背景音乐
	QSound * bgsound;

	// 玩家数
	int playerNum;
	// 飞行物链表
	QList<Flyer*> flyerList;
	// 敌机链表
	QList<EnemyPlane*> planesList;
	// 敌机发射子弹链表
	QList<Bullet*> bulletList;
	// 玩家子弹链表
	QList<Bullet*> playerBulletList;
	// 导弹链表
	QList<Missile*> missileList;
	// 爆炸链表
	QList<Bomb*> bombList;
	// 补寄链表
	QList<Supply*> supplyList;
	// 客机链表
	QList<PassengerPlane*> passengerPlaneList;
	// 乘客链表
	QList<Bullet*> passengerList;

	// Boss
	Boss * boss = NULL;
	bool bossDead;

	// 两个玩家
	PlayerPlane * player[2];
	// 玩家是否开火，由键盘事件控制
	bool playerAttackFlag[2];

	// 设置玩家
	void setPlayer();

	// 检查更新，新建飞机，新建子弹，碰撞
	void checkUpdate();

	void showPlayerMessage();

	// 菜单栏
	QMenu *menu;
	QAction *stopAction, *restartAction, *invincibleAction, *adjustAction;
	void creatMenu();

private slots:
	
	// 难度升级
	void chapterUpgrade();

	void stop();
	void restart();
	void changeMenuEnabled();

	// 无敌
	void changeInvincible();

	// 难度调节
	void adjust();

};

#endif // GAMEWINDOW_H
