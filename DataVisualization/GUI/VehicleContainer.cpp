#include "VehicleContainer.h"
#include "ui_VehicleContainer.h"

VehicleContainer::VehicleContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VehicleContainer)
{
    ui->setupUi(this);
    vehicles[1] = new VehicleWidget(this);
    this->ui->vehiclesLayout->addWidget(vehicles[1]);
}

VehicleContainer::~VehicleContainer()
{
    delete ui;
}
