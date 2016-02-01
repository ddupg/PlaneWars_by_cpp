#include "playerplane.h"

int PlayerPlane::Score = 0;

PlayerPlane::PlayerPlane(QPoint pos, QString imgPath, int speedDir, int blood) : 
	Plane(pos, imgPath, speedDir, blood) {

	this->img = this->img.scaled(PLAYER_PLANE_WIDTH, (int)(img.height() * (1.0 * PLAYER_PLANE_WIDTH / img.width())), Qt::KeepAspectRatio);
	this->setAttackPower(PLAYER_ATTACK);

	getAttackSupply = false;
}

PlayerPlane::~PlayerPlane() {

}

void PlayerPlane::Paint(QPainter * painter, QRect screen){
	painter->drawPixmap(lastPos - QPoint(width() / 2, height() / 2), img);
}

void PlayerPlane::move(QRect parentWinSize){
	int x = lastPos.x() + speed.x(), y = lastPos.y() + speed.y();
	x = std::min(x, parentWinSize.width());
	x = std::max(x, 0);
	y = std::min(y, parentWinSize.height());
	y = std::max(y, 0);
	lastPos = QPoint(x, y);
}

void PlayerPlane::getBullet(QList<Bullet*>& list){

	if (rand() % 10000 / 10000.0 < 0.1){
		for (int i = 0; i < 10; i++){
			Bullet* bullet = new Bullet(getCurPostion(), "Resources/image/bossbullet.png", PLANE_DIR_UP);
			bullet->setSpeedVector(VectorRotate(QPoint(0, -BULLET_SPEED), 360 / 20 * i));				
			bullet->setAttackPower(this->getAttackPower() / 2);
			list.append(bullet);
		}
		return;
	}

	if (!getAttackSupply){
		Bullet * bullet = new Bullet(lastPos, "Resources/image/myBullet2.png", getSpeedDir());
		bullet->setSpeedVector(QPoint(0, -BULLET_SPEED));
		bullet->setBulletSize(PLAYER_BULLET_WIDTH);
		bullet->setAttackPower(this->getAttackPower());
		list.append(bullet);
	}
	else{
		Bullet * bullet1 = new Bullet(lastPos - QPoint(width() / 4, 0), "Resources/image/myBullet2.png", getSpeedDir());
		bullet1->setSpeedVector(QPoint(0, -BULLET_SPEED));
		bullet1->setBulletSize(PLAYER_BULLET_WIDTH);
		bullet1->setAttackPower(this->getAttackPower());
		list.append(bullet1);

		Bullet * bullet2 = new Bullet(lastPos + QPoint(width() / 4, 0), "Resources/image/myBullet2.png", getSpeedDir());
		bullet2->setSpeedVector(QPoint(0, -BULLET_SPEED));
		bullet2->setBulletSize(PLAYER_BULLET_WIDTH);
		bullet2->setAttackPower(this->getAttackPower());
		list.append(bullet2);
	}
}

void PlayerPlane::getSupply(int Type){
	if (Type == BLOOD_SUPPLY_TYPE){
		this->setBlood(this->getBlood()+BLOOD_SUPPLY);
	}
	if (Type == ATTACK_SUPPLY_TYPE){
		this->getAttackSupply = true;
	}
}

void PlayerPlane::setBlood(int x){
	if (invincibleFlag)
		return ;
	x = std::min(PLAYER_BLOOD, x);
	x = std::max(x, 0);
	this->blood = x;
}

void PlayerPlane::getMissile(QList<Missile*>& list, EnemyPlane* plane){
	Missile * missile = new Missile(lastPos, "Resources/image/missile.png", getSpeedDir(), plane);
	missile->setSpeedVector(QPoint(0, -BULLET_SPEED));
	missile->setBulletSize(PLAYER_BULLET_WIDTH);
	missile->setAttackPower(this->getAttackPower() * 2);
	list.append(missile);
}

void PlayerPlane::addScore(int x){
	PlayerPlane::Score += x;
	x = std::max(x, 0);
}

int PlayerPlane::getScore(){
	return PlayerPlane::Score;
}

void PlayerPlane::changeInvincible(){
	invincibleFlag = !invincibleFlag;
}

void PlayerPlane::getAttacked(int x){
	if (invincibleFlag)
		return;
	Plane::getAttacked(x);
}