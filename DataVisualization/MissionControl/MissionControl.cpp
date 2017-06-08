#include "MissionControl.h"

#include <QDebug>

namespace MissionControl {

MissionControl::MissionControl(DisplayImage *mapFragment, QObject *parent) : QObject(parent)
{
    mapModel = new PathOverlay(new ColorMapOverlay(new ColorMapOverlay(new ColorMapOverlay(new ColorMapOverlay(mapFragment, green), yellow),red), black));
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
        newMessage(message);
    }
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
