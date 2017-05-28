#ifndef MISSIONCONTROL_H
#define MISSIONCONTROL_H

#include <QObject>
#include <QVector>

#include <Message.h>
#include <MapImageManipulation/MapFragment.h>
#include <MapImageManipulation/ColorMapOverlay.h>
#include <MapImageManipulation/PathOverlay.h>

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
    explicit MissionControl(DisplayImage *mapFragment, MainWindow *view, QObject *parent = 0);

private:
    QVector<Drone*> drones;
    Drone *getDrone(int ID);
    MainWindow *view;
    DisplayImage *mapModel;

signals:
    void newImage(DisplayImage *image);

public slots:
    void newMessage(const Message &message);
};

}

#endif // MISSIONCONTROL_H
