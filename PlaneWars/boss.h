#ifndef BOSS_H
#define BOSS_H

#include "header.h"
#include "flyer.h"
#include "bullet.h"

class Boss : public Flyer
{
public:
	Boss(QPoint, QString, int);
	~Boss();

	void getBullet(QList<Bullet*>& list);
	void move(QRect);
	void Paint(QPainter*, QRect);

	void getAttack(int);
	int getBlood();

private:

	int blood;

};


#endif