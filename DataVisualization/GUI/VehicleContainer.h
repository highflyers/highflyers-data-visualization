#ifndef VEHICLECONTAINER_H
#define VEHICLECONTAINER_H

#include <QWidget>
#include <GUI/VehicleWidget.h>
#include <QMap>

namespace Ui {
class VehicleContainer;
}

class VehicleContainer : public QWidget
{
    Q_OBJECT

public:
    explicit VehicleContainer(QWidget *parent = 0);
    ~VehicleContainer();

private:
    Ui::VehicleContainer *ui;
    QMap<int, VehicleWidget*> vehicles;
};

#endif // VEHICLECONTAINER_H
