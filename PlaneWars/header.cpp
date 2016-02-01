#include "header.h"

// int 转 QString
QString IntToQString(int x){
	std::stringstream ss;
	char s[100];
	ss << x;
	ss >> s;
	return QString(s);
}

QString DoubleToQString(double x){
	std::stringstream ss;
	char s[100];
	ss << x;
	ss >> s;
	return QString(s);
}

// 获得[L, R]区间的随机数
int getRandom(int L, int R){
	int range = R - L + 1;
	return L + rand() % range;
}

// 判断两个矩形是否相交
bool RectangleIntersection(QRect a, QRect b){
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 2; j++){
			QPoint p(a.x() + i * a.width(), a.y() + j * a.height());
			if (p.x() >= b.x() && p.x() <= b.x() + b.width() && p.y() >= b.y() && p.y() <= b.y() + b.height())
				return true;
		}
	}
	std::swap(a, b);
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 2; j++){
			QPoint p(a.x() + i * a.width(), a.y() + j * a.height());
			if (p.x() >= b.x() && p.x() <= b.x() + b.width() && p.y() >= b.y() && p.y() <= b.y() + b.height())
				return true;
		}
	}
	return false;
}

double VectorDot(QPoint a, QPoint b){
	return a.x() * b.x() + a.y() * b.y();
}

double VectorLength(QPoint a){
	return sqrt(VectorDot(a, a));
}

double VectorAngle(QPoint a, QPoint b){
	return acos(VectorDot(a, b) / VectorLength(a) / VectorLength(b));
}

QPoint VectorRotate(QPoint a, double rad){
	return QPoint(a.x() * cos(rad) - a.y() * sin(rad), a.x() * sin(rad) + a.y() * cos(rad));
}

double VectorCross(QPoint a, QPoint b){
	return a.x() * b.y() - a.y() * b.x();
}