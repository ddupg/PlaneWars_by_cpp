#ifndef ADJUST_H
#define ADJUST_H

#include <QWidget>
#include "header.h"
#include "chapter.h"

namespace Ui {
class Adjust;
}

class Adjust : public QDialog
{
    Q_OBJECT

public:
    explicit Adjust(Chapter *, QWidget *parent = 0);
    ~Adjust();

private:
    Ui::Adjust *ui;
	Chapter *chapter;

private slots:
	void OK();
};

#endif // ADJUST_H
