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
	// ��ʼλ��
	QPoint lastPos;
	// �ƶ��ٶ�
	QPoint speed;
	// ͼƬ
	QPixmap img;
	QString imgPath;
	// �ٶȷ���
	int speedDir;
	//������
	int attackPower;
};

#endif // FLYER_H
