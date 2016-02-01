#include "passengerplane.h"


PassengerPlane::PassengerPlane(QPoint pos, QString imgPath, int dir, int blood) : 
	Plane(pos, imgPath, dir, blood)
{
	this->img = this->img.scaled(1.5 * PLAYER_PLANE_WIDTH, (int)(img.height() * (1.5 * PLAYER_PLANE_WIDTH / img.width())), Qt::KeepAspectRatio);
}

PassengerPlane::~PassengerPlane(){

}

void PassengerPlane::Paint(QPainter* painter, QRect rect){
	painter->drawPixmap(getCurPostion() - QPoint(width() / 2, height() / 2), img);
}

void PassengerPlane::getBullet(QList<Bullet*>& list){
	Bullet * bullet = new Bullet(getCurPostion(), QString("Resources/image/passenger.png"), getSpeedDir());
	bullet->setSpeedVector(QPoint(0, BULLET_SPEED * getSpeedDir()));
	bullet->setBulletSize(PLAYER_BULLET_WIDTH * 2);
	bullet->Rotate180();
	list.append(bullet);
}