#include "PathOverlay.h"

#include <QtCore>
#include <QDebug>

PathOverlay::PathOverlay(DisplayImage *parentImage, QObject *parent) : MapOverlay(parent), parentImage(parentImage)
{
    customPlot = new QCustomPlot();
    pathCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);

    image = parentImage->image;
    width = image.width();
    height = image.height();

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

QPair<QGeoCoordinate, QGeoCoordinate> PathOverlay::limits() const
{
    return parentImage->limits();
}

QImage PathOverlay::toImage()
{
    QPixmap mapPixmap = customPlot->toPixmap(width, height);
    return mapPixmap.toImage();
}

int PathOverlay::absoluteLongitudeToRelative(QGeoCoordinate position)
{
    QPair<QGeoCoordinate, QGeoCoordinate> limits = this->limits();
    int result = -1;
    if(position.longitude() > limits.first.longitude() && position.longitude() < limits.second.longitude())
        result = static_cast<int>(width/(limits.second.longitude() - limits.first.longitude()) * (position.longitude() - limits.first.longitude()));

    return result;
}

int PathOverlay::absoluteLatitudeToRelative(QGeoCoordinate position)
{
    QPair<QGeoCoordinate, QGeoCoordinate> limits = this->limits();
    int result = -1;
    double unit = height/(limits.second.latitude() - limits.first.latitude());
    if(position.latitude() > limits.first.latitude() && position.latitude() < limits.second.latitude())
        result = static_cast<int>((position.latitude() - limits.first.latitude()) * unit);

    return result;
}

void PathOverlay::processData(const Message &message)
{
    static unsigned i=0;
    parentImage->processData(message);

    customPlot->xAxis->setRange(0, width);
    customPlot->yAxis->setRange(0, height);
    int x = 0;
    int y = 0;

//    Message mess;

//    mess.position.setLongitude(1+(i*0.01));
//    mess.position.setLatitude(1+(i*0.01));
//    i++;
//    qDebug() << "pos long: " << mess.position.longitude();
//    qDebug() << "pos lat: " << mess.position.latitude();
    if((x = absoluteLongitudeToRelative(message.position)) != -1){
        qDebug() << "x: " << x;
        if((y = absoluteLatitudeToRelative(message.position)) != -1){
            qDebug() << "y: " << y;
            pathData.push_back(QCPCurveData(x, x, y));
            pathCurve->data()->set(pathData, true);
            pathCurve->setPen(QPen(Qt::blue, 5.0));
        }
    }
}

QImage PathOverlay::rewriteImage()
{
    image = parentImage->rewriteImage();

    QImage overlayImage = this->toImage();

    QPainter::CompositionMode mode = QPainter::CompositionMode_Multiply;

    QImage resultImage = QImage(width, height, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&resultImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, overlayImage.scaled(width, height));
    painter.setCompositionMode(mode);
    painter.drawImage(0, 0, image.scaled(width, height));
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.fillRect(resultImage.rect(), Qt::white);
    painter.end();

    image = resultImage;

    return image;
}
