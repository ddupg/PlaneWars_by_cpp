#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "header.h"
#include "plane.h"
#include "bullet.h"

class EnemyPlane : public Plane
{
public:
	EnemyPlane(QPoint, QString, int speedDir, int blood = 1);
	~EnemyPlane();

	void Paint(QPainter *, QRect);

	void getBullet(QList<Bullet*>& list);

	void setSpeedVector(QPoint speed);

private:


private slots:
	
};



#endif // ENEMYPLANE_H