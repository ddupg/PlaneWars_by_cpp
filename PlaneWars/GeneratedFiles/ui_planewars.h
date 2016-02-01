/********************************************************************************
** Form generated from reading UI file 'planewars.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLANEWARS_H
#define UI_PLANEWARS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlaneWarsClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PlaneWarsClass)
    {
        if (PlaneWarsClass->objectName().isEmpty())
            PlaneWarsClass->setObjectName(QStringLiteral("PlaneWarsClass"));
        PlaneWarsClass->resize(600, 400);
        menuBar = new QMenuBar(PlaneWarsClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        PlaneWarsClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PlaneWarsClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PlaneWarsClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(PlaneWarsClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        PlaneWarsClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PlaneWarsClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PlaneWarsClass->setStatusBar(statusBar);

        retranslateUi(PlaneWarsClass);

        QMetaObject::connectSlotsByName(PlaneWarsClass);
    } // setupUi

    void retranslateUi(QMainWindow *PlaneWarsClass)
    {
        PlaneWarsClass->setWindowTitle(QApplication::translate("PlaneWarsClass", "PlaneWars", 0));
    } // retranslateUi

};

namespace Ui {
    class PlaneWarsClass: public Ui_PlaneWarsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLANEWARS_H
