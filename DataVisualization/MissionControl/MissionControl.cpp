#include "MissionControl.h"

#include <QDebug>

namespace MissionControl {

MissionControl::MissionControl(DisplayImage *mapFragment, QObject *parent) : QObject(parent)
{
    mapModel = new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(mapFragment, green), yellow),red), black);
}

DisplayImage* MissionControl::getDisplayImage()
{
    return mapModel;
}

void MissionControl::newMessage(const Message &message)
{
    qDebug() << message.toString();
    Drone *drone = getDrone(message.ID);
    if(drone)
    {
        if(drone->name == message.name)
        {
            mapModel->processData(message);
        }
        else
        {
            qWarning() << "Drone name mismatch (ID = " << drone->ID << ") \"" << drone->name << "\" is not \"" << message.name << "\"";
        }
    }
    else
    {
        qDebug() << "Creating new drone model for ID = " << message.ID;
        Drone *drone = new Drone();
        drone->ID = message.ID;
        drone->name = message.name;
        drones.append(drone);
        mapModel = new PathOverlay(mapModel, message.ID);
        mapModel = new CurrentLocationOverlay(mapModel, message.ID);
        newMessage(message);
    }
}

void MissionControl::reset()
{
    mapModel->reset();
}

void MissionControl::setSensitivity(double value)
{
    mapModel->setSensitivity(value);
}

Drone *MissionControl::getDrone(int ID)
{
    foreach (Drone *drone, drones) {
        if(drone->ID == ID)
        {
            return drone;
        }
    }
    return nullptr;
}

}
