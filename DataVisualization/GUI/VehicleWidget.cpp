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
    this->ui->label_name->setText(name);
    this->ui->groupBox->setTitle(QString::number(ID));

    customPlot = this->ui->chart;

    customPlot->axisRect()->setAutoMargins(QCP::msNone);
    customPlot->axisRect()->setMargins(QMargins(0,0,0,0));

    customPlot->xAxis->setRange(0, DATA_FIELDS_USED);

    bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    for(unsigned i = 0; i < DATA_FIELDS_USED; ++i)
    {
        ticks << i;
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
}

VehicleWidget::~VehicleWidget()
{
    delete ui;
}

void VehicleWidget::newMessage(const Message &message)
{
    qDebug();
    this->ui->label_pos->setText(message.position.toString().replace(',', '\n'));

    chartData.clear();
    foreach (int v, message.data) {
        chartData.append((double)v);
    }
    bars->setData(ticks, chartData);
    customPlot->yAxis->setRange(0, 1.1*((*std::max_element(chartData.begin(), chartData.end())+0.01)));
    customPlot->replot();

    lastMessageTime = QDateTime::currentDateTime();
}

void VehicleWidget::updateTime()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    this->ui->label_last_message->setText(QString::number(lastMessageTime.time().msecsTo(currentTime.time()) / 1000.0) + " s");
}
