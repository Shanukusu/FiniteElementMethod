#include "pointconfig.h"
#include "ui_pointconfig.h"

PointConfig::PointConfig(GraphicPoint *point, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PointConfig)
{
    ui->setupUi(this);
    this->point = point;
    ui->xSpinBox->setValue(point->getX());
    ui->ySpinBox->setValue(point->getY());
    ui->movableCheckBox->setChecked(point->isMovable());
    ui->valueSpinBox->setValue(point->getValue());
}

PointConfig::~PointConfig()
{
    delete ui;
}
