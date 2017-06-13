#include "CurrentLocationOverlay.h"

#include <QtCore>
#include <QDebug>
#include <qcustomplot.h>

CurrentLocationOverlay::CurrentLocationOverlay(DisplayImage *parentImage, int droneId) : MapOverlay(parentImage), droneId(droneId)
{
    customPlot = new QCustomPlot();
    plotCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);

    image = parentImage->image;

    customPlot->axisRect()->setAutoMargins(QCP::msNone);
    customPlot->axisRect()->setMargins(QMargins(0,0,0,0));
    customPlot->xAxis->grid()->setVisible(false);
    customPlot->yAxis->grid()->setVisible(false);

    plotText = new QCPItemText(customPlot);
}

CurrentLocationOverlay::~CurrentLocationOverlay()
{
    delete customPlot;
    delete plotCurve;
    delete parentImage;
}

QImage CurrentLocationOverlay::toImage()
{
    QPixmap mapPixmap = customPlot->toPixmap(getWidth(), getHeight());
    return mapPixmap.toImage();
}

void CurrentLocationOverlay::processData(const Message &message)
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
                plotData.clear();
                plotData.push_back(QCPCurveData(x-1, x-1, y-1));
                plotData.push_back(QCPCurveData(x, x, y));
                plotText->position->setCoords(x, y);
                plotText->setText(message.name);
                plotCurve->data()->set(plotData, true);
                QColor tagColor = MapOverlay::colorOf(droneId);
                tagColor.setAlpha(255);
                plotCurve->setPen(QPen(tagColor, 0.05*qMin(getWidth(), getHeight())));
                customPlot->setBackground(QColor(255,255,255,0));
            }
        }
    }
    MapOverlay::processData(message);
}
