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
	// ���¼�ʱ��
	QTimer * updateTimer;
	int updateCount = 0;

	// �ؿ���ʱ��
	QTimer * chapterTimer;
	int chapterRemainingTime;

	// ��Ϸ��ʱ��
	QTime *gameTime;
	long long runTime = 0;
	// �ؿ��Ѷ�
	Chapter *chapter;
	// ����ͼ
	QPixmap bgimg;

	// ��������
	QSound * bgsound;

	// �����
	int playerNum;
	// ����������
	QList<Flyer*> flyerList;
	// �л�����
	QList<EnemyPlane*> planesList;
	// �л������ӵ�����
	QList<Bullet*> bulletList;
	// ����ӵ�����
	QList<Bullet*> playerBulletList;
	// ��������
	QList<Missile*> missileList;
	// ��ը����
	QList<Bomb*> bombList;
	// ��������
	QList<Supply*> supplyList;
	// �ͻ�����
	QList<PassengerPlane*> passengerPlaneList;
	// �˿�����
	QList<Bullet*> passengerList;

	// Boss
	Boss * boss = NULL;
	bool bossDead;

	// �������
	PlayerPlane * player[2];
	// ����Ƿ񿪻��ɼ����¼�����
	bool playerAttackFlag[2];

	// �������
	void setPlayer();

	// �����£��½��ɻ����½��ӵ�����ײ
	void checkUpdate();

	void showPlayerMessage();

	// �˵���
	QMenu *menu;
	QAction *stopAction, *restartAction, *invincibleAction, *adjustAction;
	void creatMenu();

private slots:
	
	// �Ѷ�����
	void chapterUpgrade();

	void stop();
	void restart();
	void changeMenuEnabled();

	// �޵�
	void changeInvincible();

	// �Ѷȵ���
	void adjust();

};

#endif // GAMEWINDOW_H
