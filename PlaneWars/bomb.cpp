#include "Bomb.h"

Bomb::Bomb(QPoint pos){
	this->pos = pos;
	index = 1;
}

Bomb::~Bomb(){

}

bool Bomb::Paint(QPainter * painter){
	QPixmap img;
	QString imgPath(QString("Resources/image/bomb") + IntToQString(index) + ".png");
	img.load(imgPath);
	img = img.scaled(2 * PLANE_WIDTH, 2.0 * img.height() * img.width() / PLANE_WIDTH, Qt::KeepAspectRatio);
	painter->drawPixmap(pos - QPoint(img.width() / 2, img.height() / 2), img);
	return index++ <= 10;
}