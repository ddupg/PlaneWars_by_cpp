#include "planewars.h"

PlaneWars::PlaneWars(QWidget *parent)
: QWidget(parent, Qt::FramelessWindowHint)
{
	this->setWindowOpacity(0.8);
	setAttribute(Qt::WA_TranslucentBackground);
	bgimg.load("Resources/image/plane1.png");
	bgimg = bgimg.scaled(bgimg.width() / 2, bgimg.height() / 2, Qt::KeepAspectRatio);

	QDesktopWidget *desktop = QApplication::desktop();
	this->move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);
}

PlaneWars::~PlaneWars()
{

}

void PlaneWars::paintEvent(QPaintEvent * e){
	QPainter painter(this);
	this->resize(bgimg.width(), bgimg.height());
	painter.drawPixmap(0, 0, bgimg);
}

void PlaneWars::mouseDoubleClickEvent(QMouseEvent * e){
	this->close();
}

void PlaneWars::mousePressEvent(QMouseEvent * e){
	relativePos = this->pos() - e->globalPos();
}

void PlaneWars::mouseMoveEvent(QMouseEvent * e){
	this->move(relativePos + e->globalPos());
}

// ÓÒ¼ü²Ëµ¥
void PlaneWars::contextMenuEvent(QContextMenuEvent * e){

	QAction * newSingleGameAction = new QAction(QIcon("Resources/image/plane1.png"), "&Single Game", this);
	connect(newSingleGameAction, SIGNAL(triggered()), this, SLOT(newSingleGame()));

	QAction * newDoubleGameAction = new QAction(QIcon("Resources/image/plane1.png"), "&Double Game", this);
	connect(newDoubleGameAction, SIGNAL(triggered()), this, SLOT(newDoubleGame()));

	QAction * closeAction = new QAction(QIcon("Resources/image/exit.png"), "&Close", this);
	connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

	QMenu * menu = new QMenu();
	menu->addSeparator();
	menu->addAction(newSingleGameAction);
	menu->addAction(newDoubleGameAction);
	menu->addSeparator();
	menu->addAction(closeAction);
	menu->addSeparator();
	menu->exec(e->globalPos());
	delete menu;
}

void PlaneWars::newSingleGame(){
	game = new GameWindow(1, 1);
	game->show();
	this->hide();
}
void PlaneWars::newDoubleGame(){
	game = new GameWindow(1, 2);
	game->show();
	this->hide();
}