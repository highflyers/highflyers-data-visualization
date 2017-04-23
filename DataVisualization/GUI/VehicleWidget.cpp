#include "VehicleWidget.h"
#include "ui_VehicleWidget.h"

VehicleWidget::VehicleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VehicleWidget)
{
    ui->setupUi(this);
}

VehicleWidget::~VehicleWidget()
{
    delete ui;
}
