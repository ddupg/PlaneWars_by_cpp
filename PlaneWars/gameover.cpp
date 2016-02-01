#include "gameover.h"
#include "ui_gameover.h"

GameOver::GameOver(int flag, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);

	this->setWindowTitle("Game Over");

	if (flag == GAMEOVER){
		img.load("Resources/image/gameover.jpg");
	}
	else{
		img.load("Resources/image/youarewin.jpg");
	}
}

GameOver::~GameOver()
{
    delete ui;
}

void GameOver::paintEvent(QPaintEvent * event){
	QPainter painter(this);
	painter.drawPixmap(0, 0, this->width(), this->height(), img);
}