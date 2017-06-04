#include "ColorMapOverlay.h"
#include <QDebug>

ColorMapOverlay::ColorMapOverlay(QObject *parent) : MapOverlay(parent)
{
}

ColorMapOverlay::ColorMapOverlay(DisplayImage *parentImage, QObject* parent) : MapOverlay(parent), parentImage(parentImage)
{
    customPlot = new QCustomPlot();
    customPlot->axisRect()->setAutoMargins(QCP::msNone);
    customPlot->axisRect()->setMargins(QMargins(0,0,0,0));

    colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
    colorMap->data()->setSize(parentImage->getWidth(), parentImage->getHeight());
    colorMap->data()->setRange(QCPRange(0, 8), QCPRange(0, 8));

    colorScale = new QCPColorScale(customPlot);
    colorMap->setColorScale(colorScale);
    QCPColorGradient gradient(QCPColorGradient::gpThermal);
    colorMap->setGradient(gradient.inverted());

    customPlot->rescaleAxes();
}

ColorMapOverlay::~ColorMapOverlay()
{
    delete customPlot;
    delete colorMap;
    delete colorScale;
    delete marginGroup;
    delete parentImage;
}

QPair<QGeoCoordinate, QGeoCoordinate> ColorMapOverlay::limits() const
{
    return parentImage->limits();
}

QImage ColorMapOverlay::toImage()
{
    QPixmap mapPixmap = customPlot->toPixmap(width, height);
    return mapPixmap.toImage();
}

QImage ColorMapOverlay::processData(const Message &message)
{
    qDebug();
    /// @todo Implement operations
    image = parentImage->processData(message);
    width = image.width();
    height = image.height();
    double x, y, z;
    for (unsigned xIndex = 0; xIndex < width; xIndex += 1)
    {
        for (unsigned yIndex = 0; yIndex < height; yIndex += 1)
        {
            colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
            z = qSin(x)*qCos(y);
            z += 0.2;
            z = qMax(z, 0.0);
            colorMap->data()->setCell(xIndex, yIndex, z);
        }
    }
    colorMap->rescaleDataRange();

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
