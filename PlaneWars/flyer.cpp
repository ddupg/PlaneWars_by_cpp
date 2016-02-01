#include "flyer.h"


Flyer::Flyer(QPoint pos, QString imgPath, int speedDir){
	this->lastPos = QPoint(std::min(pos.x(), GAME_WINDOW_WIDTH - this->width() / 2), pos.y());
	this->imgPath = imgPath;
	this->img.load(imgPath);
	this->speedDir = speedDir;
	this->speed = QPoint(0, -10);
}

Flyer::~Flyer(){

}

void Flyer::setSpeedVector(QPoint speed){
	this->speed = speed;
}

QPoint Flyer::getSpeedVector(){
	return speed;
}

int Flyer::getSpeedDir(){
	return speedDir;
}

void Flyer::move(QRect parentWinSize){
	lastPos = lastPos + speed;
}

QPoint Flyer::getCurPostion(){
	return lastPos;
}

QPixmap Flyer::getImg(){
	return img;
}

int Flyer::width(){
	return img.width();
}

int Flyer::height(){
	return img.height();
}

bool Flyer::isCrashed(Flyer & b){
	QRect r1 = QRect(this->getCurPostion() - QPoint(this->width() / 2, this->height() / 2), 
		this->getCurPostion() + QPoint(this->width() / 2, this->height() / 2));
	QRect r2 = QRect(b.getCurPostion() - QPoint(b.width() / 2, b.height() / 2), 
		b.getCurPostion() + QPoint(b.width() / 2, b.height() / 2));
	return RectangleIntersection(r1, r2);
}

int Flyer::getAttackPower(){
	return attackPower;
}

void Flyer::setAttackPower(int x){
	attackPower = x;
}
void Flyer::Rotate180(){
	QMatrix mat;
	mat.rotate(180.0);
	img = img.transformed(mat, Qt::FastTransformation);
}