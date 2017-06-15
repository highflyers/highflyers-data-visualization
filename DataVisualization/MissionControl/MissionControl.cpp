#include "MissionControl.h"

#include <QDebug>

namespace MissionControl {

MissionControl::MissionControl(DisplayImage *mapFragment, QObject *parent) : QObject(parent)
{
    fullMapModel = new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(mapFragment, green, 7), green, 8), yellow, 4), yellow, 5), yellow, 6),red, 0), red, 1), red, 2), red, 3), black, 9);
    noPathMap = new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(mapFragment, green, 7), green, 8), yellow, 4), yellow, 5), yellow, 6),red, 0), red, 1), red, 2), red, 3), black, 9);
    noMarksMap = new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(mapFragment, green, 7), green, 8), yellow, 4), yellow, 5), yellow, 6),red, 0), red, 1), red, 2), red, 3), black, 9);
    dotOnlyMap = new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(new DotOverlay(mapFragment, green, 7), green, 8), yellow, 4), yellow, 5), yellow, 6),red, 0), red, 1), red, 2), red, 3), black, 9);
}

DisplayImage* MissionControl::getDisplayImage()
{
    return fullMapModel;
}

DisplayImage *MissionControl::getDisplayImage(bool pathPresent, bool marksPresent)
{
    if(!pathPresent && marksPresent)
    {
        return noPathMap;
    }
    else if(pathPresent && !marksPresent)
    {
        return noMarksMap;
    }
    else if(!pathPresent && !marksPresent)
    {
        return dotOnlyMap;
    }
    else
    {
        return fullMapModel;
    }
}

void MissionControl::newMessage(const Message &message)
{
    qDebug() << message.toString();
    Drone *drone = getDrone(message.ID);
    if(drone)
    {
        if(drone->name == message.name)
        {
            fullMapModel->processData(message);
            noPathMap->processData(message);
            noMarksMap->processData(message);
            dotOnlyMap->processData(message);
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
        fullMapModel = new PathOverlay(fullMapModel, message.ID);
        fullMapModel = new CurrentLocationOverlay(fullMapModel, message.ID);
        noPathMap = new CurrentLocationOverlay(noPathMap, message.ID);
        noMarksMap = new PathOverlay(noMarksMap, message.ID);
        newMessage(message);
    }
}

void MissionControl::reset()
{
    fullMapModel->reset();
    noPathMap->reset();
    noMarksMap->reset();
    dotOnlyMap->reset();
}

void MissionControl::setSensitivity(double value)
{
    fullMapModel->setSensitivity(value);
    noPathMap->setSensitivity(value);
    noMarksMap->setSensitivity(value);
    dotOnlyMap->setSensitivity(value);
}

void MissionControl::setFilter(QVector<bool> filter)
{
    fullMapModel->filter(filter);
    noPathMap->filter(filter);
    noMarksMap->filter(filter);
    dotOnlyMap->filter(filter);
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
