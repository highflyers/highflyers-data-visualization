#include "VehicleWidget.h"
#include "ui_VehicleWidget.h"

#include <QSharedPointer>

#include <algorithm>

VehicleWidget::VehicleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VehicleWidget)
{
    ui->setupUi(this);

    customPlot = this->ui->chart;

    customPlot->axisRect()->setAutoMargins(QCP::msNone);
    customPlot->axisRect()->setMargins(QMargins(0,0,0,0));

    customPlot->xAxis->setRange(0, DATA_FIELDS_USED);

    bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    for(unsigned i = 0; i < DATA_FIELDS_USED; ++i)
    {
        ticks << i;
        labels << QString::number(i);
        chartData << i;
    }

    customPlot->xAxis->grid()->setVisible(false);
    customPlot->yAxis->grid()->setVisible(false);
    customPlot->legend->setVisible(false);
    bars->setData(ticks, chartData);
    customPlot->yAxis->setRange(0, 1.1*((*std::max_element(chartData.begin(), chartData.end())+0.01)));
}

VehicleWidget::~VehicleWidget()
{
    delete ui;
}
