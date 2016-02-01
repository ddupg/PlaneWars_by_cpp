#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>
#include "header.h"

namespace Ui {
class GameOver;
}

class GameOver : public QDialog
{
    Q_OBJECT

public:
    explicit GameOver(int, QWidget *parent = 0);
    ~GameOver();

	void paintEvent(QPaintEvent * event);

private:
    Ui::GameOver *ui;
	QPixmap img;
};

#endif // GAMEOVER_H
