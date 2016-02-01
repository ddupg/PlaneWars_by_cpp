#ifndef CHAPTER_H
#define CHAPTER_H

#include "header.h"
#include "plane.h"
#include "bullet.h"
#include "enemyplane.h"
#include "playerplane.h"
#include "supply.h"
#include "passengerplane.h"

class Chapter
{
public:
	Chapter(int);
	~Chapter();

	int getChapterLevel();
	bool getPlaneAppearProbability();
	bool getAttackProbability();
	bool getSupplyProbability();
	int getAttackFrequency();
	QPixmap getBackGroundPixmap();
	void getEnemyPlane(QList<EnemyPlane*>&, QRect);
	void getSupply(QList<Supply*>&, QPoint);

	void setBasicAttackProbability(int);
	int getBasicAttackProbability();

	void setBasicPlaneAppearProbability(int);
	int getBasicPlaneAppearProbability();

	void setBasicSupplyProbability(int);
	int getBasicSupplyProbability();

	// 获得客机
	void Chapter::getPassengerPlane(QList<PassengerPlane*>& list, QRect);

private:
	
	// 关卡等级
	int chapterLevel;
	// 敌机出现概率
	double basicPlaneAppearProbability, PlaneAppearProbability;
	// 敌机攻击频率
	double basicAttackProbability, AttackProbability;
	// 补寄出现概率
	double basicSupplyProbability, SupplyProbability;
	// 背景图
	QPixmap bgmap;

};

#endif // CHAPTER_H