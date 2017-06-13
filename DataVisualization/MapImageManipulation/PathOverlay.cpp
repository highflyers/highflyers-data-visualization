#include "PathOverlay.h"

#include <QtCore>
#include <QDebug>

PathOverlay::PathOverlay(DisplayImage *parentImage) : MapOverlay(parentImage)
{
    customPlot = new QCustomPlot();
    pathCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);

    image = parentImage->image;

    customPlot->axisRect()->setAutoMargins(QCP::msNone);
    customPlot->axisRect()->setMargins(QMargins(0,0,0,0));
    customPlot->xAxis->grid()->setVisible(false);
    customPlot->yAxis->grid()->setVisible(false);
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
    static unsigned i=0;
    parentImage->processData(message);

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
            pathCurve->setPen(QPen(Qt::blue, 2.0));
        }
    }
}

QImage PathOverlay::rewriteImage()
{
    image = parentImage->rewriteImage();

    QImage overlayImage = this->toImage();

    QPainter::CompositionMode mode = QPainter::CompositionMode_Multiply;

    QImage resultImage = QImage(getWidth(), getHeight(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&resultImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, overlayImage.scaled(getWidth(), getHeight()));
    painter.setCompositionMode(mode);
    painter.drawImage(0, 0, image.scaled(getWidth(), getHeight()));
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.fillRect(resultImage.rect(), Qt::white);
    painter.end();

    image = resultImage;

    return image;
}
