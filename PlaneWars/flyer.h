#ifndef FLYER_H
#define FLYER_H

#include "header.h"

class Flyer
{
public:
	Flyer(QPoint, QString, int speedDir);
	~Flyer();

	void move(QRect);


	QPoint getCurPostion();
	QPixmap getImg();

	void setSpeedVector(QPoint);
	QPoint getSpeedVector();

	void Rotate180();

	virtual void Paint(QPainter *, QRect) = 0;
	int width();
	int height();

	bool isCrashed(Flyer &);

	int getSpeedDir();

	void setAttackPower(int);
	int getAttackPower();

protected:
	// 起始位置
	QPoint lastPos;
	// 移动速度
	QPoint speed;
	// 图片
	QPixmap img;
	QString imgPath;
	// 速度方向
	int speedDir;
	//攻击力
	int attackPower;
};

#endif // FLYER_H
