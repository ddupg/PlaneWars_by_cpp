
#include "boss.h"

Boss::Boss(QPoint pos, QString imgPath, int dir) : Flyer(pos, imgPath, dir){
	img.load(imgPath);
	img = img.scaled(PLAYER_PLANE_WIDTH * 4, 4.0 * img.height() * PLAYER_PLANE_WIDTH / img.width());
	blood = BOSS_BLOOD;
}

Boss::~Boss(){

}

void Boss::getBullet(QList<Bullet*>& list){
	if (rand() % 10000 / 10000.0 < 0.02){
		for (int i = 0; i < 20; i++){
			Bullet* bullet = new Bullet(getCurPostion(), "Resources/image/bossbullet.png", PLANE_DIR_UP);
			bullet->setSpeedVector(VectorRotate(QPoint(0, -BULLET_SPEED), 360 / 20 * i));
			bullet->setAttackPower(PLANE_ATTACK);
			list.append(bullet);
		}
	}
}
void Boss::move(QRect rect){
	int lx = getCurPostion().x() - width() / 2, rx = getCurPostion().x() + width() / 2;
	int ly = getCurPostion().y() - height() / 2, ry = getCurPostion().y() + height() / 2;
	if (lx < 0 || rx > rect.width()){
		speed.setX(-speed.x());
	}
	if (ly < 0 || ry > rect.height()){
		speed.setY(-speed.y());
	}
	lastPos = lastPos + speed;
}

void Boss::Paint(QPainter* painter, QRect rect){
	painter->drawPixmap(getCurPostion() - QPoint(width() / 2, height() / 2), img);
}

void Boss::getAttack(int x){
	blood = std::max(0, blood - x);
}

int Boss::getBlood(){
	return blood;
}