#include "plane.h"


Plane::Plane(QPoint pos, QString imgPath, int speedDir, int blood) : Flyer(pos, imgPath, speedDir) {

	setSpeedVector(QPoint(0, speedDir * PLANE_SPEED));
	this->blood = blood;
}

Plane::~Plane(){

}

int Plane::getBlood(){
	return this->blood;
}

void Plane::getAttacked(int x){
	blood = std::max(blood - x, 0);
}

void Plane::setBlood(int blood){
	this->blood = blood;
}