#include "VehicleWidget.h"
#include "ui_VehicleWidget.h"

#include <QSharedPointer>

#include <algorithm>
#include <QDebug>

VehicleWidget::VehicleWidget(int ID, const QString &name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VehicleWidget)
{
    ui->setupUi(this);
    this->ui->groupBox->setTitle(QString::number(ID));

    customPlot = this->ui->chart;

    customPlot->axisRect()->setAutoMargins(QCP::msNone);
    customPlot->axisRect()->setMargins(QMargins(0,0,0,0));

    customPlot->xAxis->setRange(0, DATA_FIELDS_USED);

    bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    for(unsigned i = 0; i < DATA_FIELDS_USED; ++i)
    {
        ticks << i + 0.5;
        labels << QString::number(i);
    }

    customPlot->xAxis->grid()->setVisible(false);
    customPlot->yAxis->grid()->setVisible(false);
    customPlot->legend->setVisible(false);

    lastMessageTime = QDateTime::currentDateTime();

    elapsedTimeTimer = new QTimer(this);
    elapsedTimeTimer->setSingleShot(false);
    elapsedTimeTimer->setInterval(TIMER_INTERVAL);
    connect(elapsedTimeTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
    elapsedTimeTimer->start();

    connect(customPlot, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(chartClicked()));
}

VehicleWidget::~VehicleWidget()
{
    delete ui;
}

void VehicleWidget::newMessage(const Message &message)
{
    qDebug();
    this->ui->groupBox->setTitle(QString::number(message.ID) + " - " + message.name);
//    this->ui->label_pos->setText(message.position.toString().replace(',', '\n'));
    this->ui->label_pos->setText(message.position.toString());

    double localMin = *std::min_element(message.data.begin(), message.data.end());
    if(chartMinMaxSet)
    {
        chartMin = chartMin < localMin ? chartMin : localMin;
    }
    else
    {
        chartMin = localMin;
        chartMinMaxSet = true;
    }

    chartData.clear();
    foreach (int v, message.data) {
        chartData.append((double)v - chartMin);
    }
    bars->setData(ticks, chartData);

    double localMax = *std::max_element(chartData.begin(), chartData.end());
    if(chartMinMaxSet)
    {
        chartMax = chartMax > localMax ? chartMax : localMax;
    }
    else
    {
        chartMax = localMax;
        chartMinMaxSet = true;
    }
    customPlot->yAxis->setRange(0, 1.1*(chartMax+0.01));
    customPlot->replot();

    lastMessageTime = QDateTime::currentDateTime();
}

void VehicleWidget::updateTime()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    double timeDiff = lastMessageTime.time().msecsTo(currentTime.time()) / 1000.0;
    this->ui->label_last_message->setText(QString::number(timeDiff) + " s");
    if(timeDiff > timeThreshold)
    {
        this->ui->label_last_message->setStyleSheet(TIME_TEXT_LATE);
    }
    else
    {
        this->ui->label_last_message->setStyleSheet(TIME_TEXT_NORMAL);
    }
}

void VehicleWidget::chartClicked()
{
    chartMinMaxSet = false;
}
