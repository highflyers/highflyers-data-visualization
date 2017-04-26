#include "PathOverlay.h"

#include <QtCore>

PathOverlay::PathOverlay(unsigned width, unsigned height, QObject *parent) : MapOverlay(parent), width(width), height(height)
{
    customPlot = new QCustomPlot();
    pathCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);

    customPlot->axisRect()->setAutoMargins(QCP::msNone);
    customPlot->axisRect()->setMargins(QMargins(0,0,0,0));
    customPlot->xAxis->grid()->setVisible(false);
    customPlot->yAxis->grid()->setVisible(false);
}

QImage PathOverlay::toImage()
{
    QPixmap mapPixmap = customPlot->toPixmap(width, height);
    return mapPixmap.toImage();
}

void PathOverlay::processData(const Message &message)
{
    customPlot->xAxis->setRange(-2, 1.5);
    customPlot->yAxis->setRange(0, 800);
    const int pointCount = 500;
    QVector<QCPCurveData> pathData(pointCount);
    for (int i=0; i<pointCount; ++i)
    {
      pathData[i] = QCPCurveData(i, qSin(i/20.0), i);
    }
    pathCurve->data()->set(pathData, true);
    pathCurve->setPen(QPen(Qt::blue, 5.0));
}
