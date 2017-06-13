#include "PathOverlay.h"

#include <QtCore>
#include <QDebug>

PathOverlay::PathOverlay(DisplayImage *parentImage, int droneId) : MapOverlay(parentImage), droneId(droneId)
{
    customPlot = new QCustomPlot();
    pathCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);

    image = parentImage->image;

    customPlot->axisRect()->setAutoMargins(QCP::msNone);
    customPlot->axisRect()->setMargins(QMargins(0,0,0,0));
    customPlot->xAxis->grid()->setVisible(false);
    customPlot->yAxis->grid()->setVisible(false);
    customPlot->setBackground(QColor(255,255,255,0));
}

PathOverlay::~PathOverlay()
{
    delete customPlot;
    delete pathCurve;
    delete parentImage;
}

QImage PathOverlay::toImage()
{
    QPixmap mapPixmap = customPlot->toPixmap(getWidth(), getHeight());
    return mapPixmap.toImage();
}

void PathOverlay::processData(const Message &message)
{
    if(message.ID == droneId)
    {
        customPlot->xAxis->setRange(0, getWidth());
        customPlot->yAxis->setRange(0, getHeight());
        int x = 0;
        int y = 0;

        if((x = absoluteLongitudeToRelative(message.position)) != -1){
            qDebug() << "x: " << x;
            if((y = absoluteLatitudeToRelative(message.position)) != -1){
                qDebug() << "y: " << y;
                pathData.push_back(QCPCurveData(x, x, y));
                pathCurve->data()->set(pathData, true);
                pathCurve->setPen(QPen(MapOverlay::colorOf(message.ID), 2.0));
            }
        }
    }
    MapOverlay::processData(message);
}
