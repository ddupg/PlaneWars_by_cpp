

#include "missile.h"

Missile::Missile(QPoint pos, QString imgPath, int dir, Flyer * plane) : 
	Bullet(pos, imgPath, dir){
	//goal = plane;
}

Missile::~Missile(){

}

void Missile::move(){
	//if ((*goal) != NULL){
	//	moveto((*goal)->getCurPostion());
	//}
	//else{
	//	lastPos = lastPos + speed;
	//}
}