#ifndef MISSILE_H
#define MISSILE_H

#include "header.h"
#include "enemyplane.h"
#include "bullet.h"

class Missile : public Bullet
{
public:
	Missile(QPoint, QString, int, Flyer * );
	~Missile();

	void move();

private:

};

#endif