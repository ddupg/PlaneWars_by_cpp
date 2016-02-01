#ifndef BULLET_H
#define BULLET_H

#include "header.h"
#include "flyer.h"

class Bullet : public Flyer
{
public:
	Bullet(QPoint, QString, int);
	~Bullet();

	void Paint(QPainter *, QRect);
	void setBulletSize(int);
	void moveto(QPoint);
	void setSpeedVector(QPoint);

private:
	QPoint point;
	int velocity;
	QPixmap bulletImg;

};


#endif // BULLET_H