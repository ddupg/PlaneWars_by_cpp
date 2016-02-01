#ifndef BOMB_H
#define BOMB_H

#include "header.h"

class Bomb
{
public:
	Bomb(QPoint);
	~Bomb();
	bool Paint(QPainter * painter);

private:
	QPoint pos;
	int index = 0;
};



#endif	// BOMB_H