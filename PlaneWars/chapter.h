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

	// ��ÿͻ�
	void Chapter::getPassengerPlane(QList<PassengerPlane*>& list, QRect);

private:
	
	// �ؿ��ȼ�
	int chapterLevel;
	// �л����ָ���
	double basicPlaneAppearProbability, PlaneAppearProbability;
	// �л�����Ƶ��
	double basicAttackProbability, AttackProbability;
	// ���ĳ��ָ���
	double basicSupplyProbability, SupplyProbability;
	// ����ͼ
	QPixmap bgmap;

};

#endif // CHAPTER_H