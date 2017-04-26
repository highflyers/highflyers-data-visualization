#ifndef VEHICLEWIDGET_H
#define VEHICLEWIDGET_H

#include <QWidget>
#include <QString>
#include <QVector>

#include <qcustomplot.h>

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

    static const unsigned DATA_FIELDS_USED = 10;
    QCustomPlot *customPlot;
    QCPBars *bars;
    QVector<double> ticks;
    QVector<QString> labels;
    QVector<double> chartData;
};

#endif // VEHICLEWIDGET_H
