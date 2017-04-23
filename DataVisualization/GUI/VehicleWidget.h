#ifndef VEHICLEWIDGET_H
#define VEHICLEWIDGET_H

#include <QWidget>

namespace Ui {
class VehicleWidget;
}

class VehicleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VehicleWidget(QWidget *parent = 0);
    ~VehicleWidget();

private:
    Ui::VehicleWidget *ui;
};

#endif // VEHICLEWIDGET_H
