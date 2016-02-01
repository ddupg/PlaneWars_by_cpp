#ifndef PLANE_H
#define PLANE_H

#include "header.h"
#include "bullet.h"

class Plane : public Flyer
{
public:
	// �������꣬ Ѫ��
	Plane(QPoint, QString, int, int blood = 1);
	~Plane();

	void getAttacked(int);
	int getBlood();
	void setBlood(int);

	virtual void getBullet(QList<Bullet*>& list) = 0;

private:

protected:
	//Ѫ��
	int blood;

private slots:
	
};

#endif // PLANE_H