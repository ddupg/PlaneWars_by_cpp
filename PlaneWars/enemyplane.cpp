#include "enemyplane.h"


EnemyPlane::EnemyPlane(QPoint pos, QString imgPath, int speedDir, int blood) :
	Plane(pos, imgPath, speedDir, blood){

	this->img = this->img.scaled(PLANE_WIDTH, (int)(img.height() * (1.0 * PLANE_WIDTH / img.width())), Qt::KeepAspectRatio);

}

EnemyPlane::~EnemyPlane() {

}

void EnemyPlane::Paint(QPainter * painter, QRect screen){
	painter->drawPixmap(getCurPostion() - QPoint(width() / 2, height() / 2), img);
}

void EnemyPlane::getBullet(QList<Bullet*>& list){
	Bullet * bullet = new Bullet(getCurPostion(), QString("Resources/image/bullet2.png"), getSpeedDir());
	bullet->setSpeedVector(QPoint(0, BULLET_SPEED * getSpeedDir()));
	bullet->setAttackPower(this->getAttackPower());
	list.append(bullet);
}

void EnemyPlane::setSpeedVector(QPoint speed){

	QMatrix matrix;
	QPoint a = this->speed, b = speed;
	double rad;
	if (VectorCross(a, b) <= 0){
		rad = VectorAngle(a, b) * 180.0;
	}
	else{
		rad = 360 - VectorAngle(a, b) * 180.0;
	}
	matrix.rotate(rad);
	img = img.transformed(matrix, Qt::FastTransformation);
	this->speed = speed;
}