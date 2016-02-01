#ifndef SUPPLY_H
#define SUPPLY_H

#include "header.h"
#include "flyer.h"

class Supply : public Flyer
{
public:
	Supply(int Type, QPoint, QString, int speedDir);
	~Supply();
	int getSupplyType();
	void getSupply(QList<Supply*>& list);
	void Paint(QPainter*, QRect);

private:
	int supplyType;
};

#endif  // SUPPLY_H