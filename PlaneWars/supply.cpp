#include "supply.h"

Supply::Supply(int Type, QPoint pos, QString imgPath, int speedDir) : Flyer(pos, imgPath, speedDir){
	this->supplyType = Type;
	this->img = this->img.scaled(PLANE_WIDTH, (int)(img.height() * (1.0 * PLANE_WIDTH / img.width())), Qt::KeepAspectRatio);
}

Supply::~Supply(){

}

int Supply::getSupplyType(){
	return supplyType;
}

void Supply::getSupply(QList<Supply*>& list){
	if (supplyType == ATTACK_SUPPLY_TYPE){

		this->img = this->img.scaled(PLANE_WIDTH, (int)(img.height() * (1.0 * PLANE_WIDTH / img.width())), Qt::KeepAspectRatio);
	}
	else if(supplyType == BLOOD_SUPPLY_TYPE) {
		this->img = this->img.scaled(PLANE_WIDTH, (int)(img.height() * (1.0 * PLANE_WIDTH / img.width())), Qt::KeepAspectRatio);
	}
}

void Supply::Paint(QPainter* painter, QRect){
	painter->drawPixmap(getCurPostion() - QPoint(width() / 2, height() / 2), img);
}