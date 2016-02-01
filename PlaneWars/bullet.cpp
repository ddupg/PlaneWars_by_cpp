#include "bullet.h"


Bullet::Bullet(QPoint pos, QString imgPath, int speedDir) : Flyer(pos, imgPath, speedDir) {
	
	this->img = this->img.scaled(BULLET_WIDTH, int(1.0 * img.height() * BULLET_WIDTH / img.width()), Qt::KeepAspectRatio);
}

Bullet::~Bullet(){

}

void Bullet::Paint(QPainter * painter, QRect){

	QPoint a(0, -10), b = this->speed;
	double rad;
	if (VectorCross(a, b) <= 0){
		rad = VectorAngle(a, b) / acos(-1.0) * 180.0;
	}
	else{
		rad = -VectorAngle(a, b) / acos(-1.0) * 180.0;
	}

	QPixmap tmpImg = img;
	QTransform transformed;
	transformed.rotate(-rad);
	painter->drawPixmap(getCurPostion() - QPoint(width() / 2, height() / 2), img.transformed(transformed));
}

void Bullet::setBulletSize(int sz){
	img.load(imgPath);
	img = img.scaled(sz, int(1.0 * img.height() * sz / img.width()), Qt::KeepAspectRatio);
}

void Bullet::setSpeedVector(QPoint speed){
	this->speed = speed;
}

void Bullet::moveto(QPoint pos){
	QPoint a = getSpeedVector(), b = pos - getCurPostion();
	double alength = VectorLength(a), blength = VectorLength(b);
	double rad;
	if (VectorCross(a, b) <= 0){
		rad = VectorAngle(a, b) / acos(-1.0) * 180.0;
	}
	else{
		rad = -VectorAngle(a, b) / acos(-1.0) * 180.0;
	}
	a = b * alength / blength;
	setSpeedVector(a);
	lastPos = lastPos + getSpeedVector();
}