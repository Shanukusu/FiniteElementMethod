#include "pointconfig.h"
#include "ui_pointconfig.h"
#include <QPushButton>

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

    connect(ui->buttonBox->buttons()[0], &QPushButton::clicked,
            this, &PointConfig::okButtonClicked);

    connect(ui->buttonBox->buttons()[1], &QPushButton::clicked,
            this, &PointConfig::cancelButtonClicked);
}

PointConfig::~PointConfig()
{
    delete ui;
}

void PointConfig::okButtonClicked()
{
    emit this->closed();
    this->close();
}

void PointConfig::cancelButtonClicked()
{
    emit this->closed();
    this->close();
}
