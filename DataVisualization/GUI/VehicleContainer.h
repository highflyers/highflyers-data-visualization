#ifndef VEHICLECONTAINER_H
#define VEHICLECONTAINER_H

#include <QWidget>
#include <GUI/VehicleWidget.h>
#include <QMap>

#include <MissionControl/MissionControl.h>

namespace Ui {
class VehicleContainer;
}

class VehicleContainer : public QWidget
{
    Q_OBJECT

public:
    explicit VehicleContainer(QWidget *parent = 0);
    ~VehicleContainer();

public slots:
    void newMessage(const Message &message);

private:
    Ui::VehicleContainer *ui;
    QMap<int, VehicleWidget*> vehicles;

    /**
     * @brief Creates a VehicleWidget for specified drone
     * A weiget is added to layout
     * @param drone: drone object containing its ID and name
     */
    void addDrone(const MissionControl::Drone &drone);
};

#endif // VEHICLECONTAINER_H
