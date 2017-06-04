#include "VehicleContainer.h"
#include "ui_VehicleContainer.h"

VehicleContainer::VehicleContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VehicleContainer)
{
    ui->setupUi(this);
}

VehicleContainer::~VehicleContainer()
{
    delete ui;
}

void VehicleContainer::newMessage(const Message &message)
{
    qDebug() << "ID =" << message.ID;
    if(!vehicles.contains(message.ID))
    {
        MissionControl::Drone drone;
        drone.ID = message.ID;
        drone.name = message.name;
        addDrone(drone);
    }
    vehicles[message.ID]->newMessage(message);
}

void VehicleContainer::addDrone(const MissionControl::Drone &drone)
{
    qDebug();
    VehicleWidget *widget = new VehicleWidget(drone.ID, drone.name, this);
    this->ui->vehiclesLayout->addWidget(widget);
    vehicles[drone.ID] = widget;
}
