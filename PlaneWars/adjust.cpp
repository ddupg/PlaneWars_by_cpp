#include "adjust.h"
#include "ui_adjust.h"

Adjust::Adjust(Chapter *chapter, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Adjust)
{
    ui->setupUi(this);

	setWindowTitle("Adjust");

	this->chapter = chapter;
	this->ui->PlaneAppearSlider->setValue(chapter->getBasicPlaneAppearProbability());
	this->ui->AttackProbabilitySlider->setValue(chapter->getBasicAttackProbability());
	this->ui->SupplyProbabilitySlider->setValue(chapter->getBasicSupplyProbability());

	connect(ui->okButton, SIGNAL(pressed()), this, SLOT(OK()));
	connect(ui->cancelButton, SIGNAL(pressed()), this, SLOT(close()));
}

Adjust::~Adjust()
{
    delete ui;
}

void Adjust::OK(){
	this->chapter->setBasicPlaneAppearProbability(ui->PlaneAppearSlider->value());
	this->chapter->setBasicAttackProbability(ui->AttackProbabilitySlider->value());
	this->chapter->setBasicSupplyProbability(ui->SupplyProbabilitySlider->value());
	this->close();
}