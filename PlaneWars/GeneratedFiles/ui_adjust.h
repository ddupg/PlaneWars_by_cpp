/********************************************************************************
** Form generated from reading UI file 'adjust.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADJUST_H
#define UI_ADJUST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Adjust
{
public:
    QLabel *planeAppearLabel;
    QSlider *PlaneAppearSlider;
    QLabel *AttackProbabilityLabel;
    QSlider *AttackProbabilitySlider;
    QLabel *SupplyProbabilityLabel;
    QSlider *SupplyProbabilitySlider;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QWidget *Adjust)
    {
        if (Adjust->objectName().isEmpty())
            Adjust->setObjectName(QStringLiteral("Adjust"));
        Adjust->resize(432, 300);
        planeAppearLabel = new QLabel(Adjust);
        planeAppearLabel->setObjectName(QStringLiteral("planeAppearLabel"));
        planeAppearLabel->setGeometry(QRect(41, 61, 144, 16));
        PlaneAppearSlider = new QSlider(Adjust);
        PlaneAppearSlider->setObjectName(QStringLiteral("PlaneAppearSlider"));
        PlaneAppearSlider->setGeometry(QRect(191, 61, 161, 22));
        PlaneAppearSlider->setOrientation(Qt::Horizontal);
        AttackProbabilityLabel = new QLabel(Adjust);
        AttackProbabilityLabel->setObjectName(QStringLiteral("AttackProbabilityLabel"));
        AttackProbabilityLabel->setGeometry(QRect(41, 111, 141, 16));
        AttackProbabilitySlider = new QSlider(Adjust);
        AttackProbabilitySlider->setObjectName(QStringLiteral("AttackProbabilitySlider"));
        AttackProbabilitySlider->setGeometry(QRect(190, 110, 161, 22));
        AttackProbabilitySlider->setOrientation(Qt::Horizontal);
        SupplyProbabilityLabel = new QLabel(Adjust);
        SupplyProbabilityLabel->setObjectName(QStringLiteral("SupplyProbabilityLabel"));
        SupplyProbabilityLabel->setGeometry(QRect(40, 160, 141, 16));
        SupplyProbabilitySlider = new QSlider(Adjust);
        SupplyProbabilitySlider->setObjectName(QStringLiteral("SupplyProbabilitySlider"));
        SupplyProbabilitySlider->setGeometry(QRect(190, 160, 160, 22));
        SupplyProbabilitySlider->setOrientation(Qt::Horizontal);
        widget = new QWidget(Adjust);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(190, 250, 158, 25));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        okButton = new QPushButton(widget);
        okButton->setObjectName(QStringLiteral("okButton"));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(widget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        retranslateUi(Adjust);

        QMetaObject::connectSlotsByName(Adjust);
    } // setupUi

    void retranslateUi(QWidget *Adjust)
    {
        Adjust->setWindowTitle(QApplication::translate("Adjust", "Form", 0));
        planeAppearLabel->setText(QApplication::translate("Adjust", "Plane Appear Probability", 0));
        AttackProbabilityLabel->setText(QApplication::translate("Adjust", "Attack Probability", 0));
        SupplyProbabilityLabel->setText(QApplication::translate("Adjust", "Supply Probability", 0));
        okButton->setText(QApplication::translate("Adjust", "OK", 0));
        cancelButton->setText(QApplication::translate("Adjust", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class Adjust: public Ui_Adjust {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADJUST_H
