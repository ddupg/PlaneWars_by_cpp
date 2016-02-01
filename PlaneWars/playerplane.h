#ifndef PLAYERPLANE_H
#define PLAYERPLANE_H

#include "header.h"
#include "plane.h"
#include "bullet.h"
#include "missile.h"

class PlayerPlane : public Plane
{
public:
	PlayerPlane(QPoint pos, QString imgPath, int speedDir, int blood = PLAYER_BLOOD);
	~PlayerPlane();

	void Paint(QPainter * , QRect);

	void move(QRect parentWinSize);

	void getBullet(QList<Bullet*>& list);

	void getSupply(int);

	void setBlood(int);
	void getAttacked(int);

	void getMissile(QList<Missile*>& list, EnemyPlane* plane);

	static void addScore(int);
	static int getScore();

	void changeInvincible();

private:
	static int Score;
	bool getAttackSupply;
	bool invincibleFlag = false;
};



#endif // PLAYERPLANE_H