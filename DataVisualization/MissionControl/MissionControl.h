#ifndef MISSIONCONTROL_H
#define MISSIONCONTROL_H

#include <QObject>
#include <QVector>

#include <Message.h>
#include <MapImageManipulation/MapFragment.h>
#include <MapImageManipulation/ColorMapOverlay.h>
#include <MapImageManipulation/PathOverlay.h>
#include <MapImageManipulation/DotOverlay.h>
#include <MapImageManipulation/CurrentLocationOverlay.h>

#include <GUI/VehicleWidget.h>

class MainWindow;

namespace MissionControl {

struct Drone
{
    int ID;
    QString name;
    bool isPathOverlayActive;
};

class MissionControl : public QObject
{
    Q_OBJECT
public:
    explicit MissionControl(DisplayImage *mapFragment, QObject *parent = 0);

    DisplayImage *getDisplayImage();

private:
    QVector<Drone*> drones;
    Drone *getDrone(int ID);
    DisplayImage *mapModel;


public slots:
    void newMessage(const Message &message);
};

}

#endif // MISSIONCONTROL_H
