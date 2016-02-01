#ifndef PASSENGERPLANE_H
#define PASSENGERPLANE_H

#include "header.h"
#include "plane.h"

class PassengerPlane : public Plane
{
public:
	PassengerPlane(QPoint, QString, int, int blood = 1);
	~PassengerPlane ();

	void getBullet(QList<Bullet*>& list);
	void Paint(QPainter *, QRect);

private:

};


#endif