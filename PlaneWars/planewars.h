#ifndef PLANEWARS_H
#define PLANEWARS_H

#include <QtWidgets/QMainWindow>
#include "ui_planewars.h"
#include "gamewindow.h"
#include "header.h"

class PlaneWars : public QWidget
{
	Q_OBJECT

public:
	PlaneWars(QWidget *parent = 0);
	~PlaneWars();

	void paintEvent(QPaintEvent * event);
	void mousePressEvent(QMouseEvent * event);
	void mouseMoveEvent(QMouseEvent * event);
	void mouseDoubleClickEvent(QMouseEvent * event);
	void contextMenuEvent(QContextMenuEvent * event);

private:
	//Ui::PlaneWarsClass ui;
	QPixmap bgimg;
	QPoint relativePos;
	GameWindow * game;

private slots:
	void newSingleGame();
	void newDoubleGame();
};

#endif // PLANEWARS_H
