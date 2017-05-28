#include "MissionControl.h"

#include <QDebug>

namespace MissionControl {

MissionControl::MissionControl(DisplayImage *mapFragment, MainWindow *view, QObject *parent) : view(view), QObject(parent)
{
    mapModel = new PathOverlay(new ColorMapOverlay(mapFragment));
}

void MissionControl::newMessage(const Message &message)
{
    qDebug() << message.ID;
    Drone *drone = getDrone(message.ID);
    if(drone)
    {
        if(drone->name == message.name)
        {
            mapModel->processData(message);
            emit newImage(mapModel);
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
