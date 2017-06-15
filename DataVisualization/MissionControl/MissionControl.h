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
    DisplayImage *getDisplayImage(bool pathPresent, bool marksPresent);

private:
    QVector<Drone*> drones;
    Drone *getDrone(int ID);
    DisplayImage *fullMapModel, *noPathMap, *noMarksMap, *dotOnlyMap;


public slots:
    void newMessage(const Message &message);
    void reset();
    void setSensitivity(double value);
    void setFilter(QVector<bool> filter);
};

}

#endif // MISSIONCONTROL_H
