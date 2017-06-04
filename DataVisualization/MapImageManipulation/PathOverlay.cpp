#include "PathOverlay.h"

#include <QtCore>
#include <QDebug>

PathOverlay::PathOverlay(DisplayImage *parentImage, QObject *parent) : MapOverlay(parent), parentImage(parentImage)
{
    customPlot = new QCustomPlot();
    pathCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);

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

QImage PathOverlay::processData(const Message &message)
{
    qDebug();
    image = parentImage->processData(message);
    width = image.width();
    height = image.height();

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
