#ifndef VEHICLEWIDGET_H
#define VEHICLEWIDGET_H

#include <QWidget>
#include <QString>
#include <QVector>

#include <QDateTime>
#include <QTimer>

#include <qcustomplot.h>

#include <Message.h>

namespace Ui {
class VehicleWidget;
}

class VehicleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VehicleWidget(int ID, const QString &name, QWidget *parent = 0);
    ~VehicleWidget();

public slots:
    void newMessage(const Message &message);

private:
    Ui::VehicleWidget *ui;
    QTimer *elapsedTimeTimer;
    static const unsigned TIMER_INTERVAL = 100;
    static const unsigned DATA_FIELDS_USED = 10;
    QCustomPlot *customPlot;
    QCPBars *bars;
    QVector<double> ticks;
    QVector<QString> labels;
    QVector<double> chartData;
    QDateTime lastMessageTime;
    bool chartMinMaxSet = false;
    double chartMin, chartMax;

    const unsigned timeThreshold = 10;
    const QString TIME_TEXT_NORMAL = "";
    const QString TIME_TEXT_LATE = "QLabel { background-color : red; color : black; }";


private slots:
    void updateTime();
    void chartClicked();
};

#endif // VEHICLEWIDGET_H
