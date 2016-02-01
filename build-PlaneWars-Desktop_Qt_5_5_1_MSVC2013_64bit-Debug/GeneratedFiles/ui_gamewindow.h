/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QLabel *player1BloodLabel;
    QLabel *player1ScoreLabel;
    QLabel *player2BloodLabel;
    QLabel *player2ScoreLabel;

    void setupUi(QWidget *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName(QStringLiteral("GameWindow"));
        GameWindow->resize(801, 600);
        player1BloodLabel = new QLabel(GameWindow);
        player1BloodLabel->setObjectName(QStringLiteral("player1BloodLabel"));
        player1BloodLabel->setGeometry(QRect(24, 24, 100, 20));
        player1ScoreLabel = new QLabel(GameWindow);
        player1ScoreLabel->setObjectName(QStringLiteral("player1ScoreLabel"));
        player1ScoreLabel->setGeometry(QRect(140, 52, 54, 20));
        player2BloodLabel = new QLabel(GameWindow);
        player2BloodLabel->setObjectName(QStringLiteral("player2BloodLabel"));
        player2BloodLabel->setGeometry(QRect(24, 52, 100, 20));
        player2ScoreLabel = new QLabel(GameWindow);
        player2ScoreLabel->setObjectName(QStringLiteral("player2ScoreLabel"));
        player2ScoreLabel->setGeometry(QRect(140, 24, 54, 20));

        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QWidget *GameWindow)
    {
        GameWindow->setWindowTitle(QApplication::translate("GameWindow", "Form", 0));
        player1BloodLabel->setText(QString());
        player1ScoreLabel->setText(QString());
        player2BloodLabel->setText(QString());
        player2ScoreLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
