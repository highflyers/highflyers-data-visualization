#include "DisplayImage.h"
#include <QPainter>
#include <QImage>

DisplayImage::DisplayImage(DisplayImage *parentImage) : QObject(parentImage), parentImage(parentImage)
{

}

QPair<QGeoCoordinate, QGeoCoordinate> DisplayImage::limits() const
{
    if(parentImage)
    {
        return parentImage->limits();
    }
    else
    {
        QGeoCoordinate coord;
        return QPair<QGeoCoordinate, QGeoCoordinate>(coord, coord);
    }
}

unsigned DisplayImage::getWidth()
{
    if(parentImage)
    {
        return parentImage->getWidth();
    }
    else
    {
        return 0;
    }
}

unsigned DisplayImage::getHeight()
{
    if(parentImage)
    {
        return parentImage->getHeight();
    }
    else
    {
        return 0;
    }
}

QImage DisplayImage::rewriteImage()
{
    image = parentImage->rewriteImage();

    QImage overlayImage = this->toImage();

//    QPainter::CompositionMode mode = QPainter::CompositionMode_Multiply;
    QPainter::CompositionMode mode = QPainter::CompositionMode_Overlay;

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

void DisplayImage::reset()
{
    if(parentImage)
    {
        parentImage->reset();
    }
}

void DisplayImage::setSensitivity(double value)
{
    if(parentImage)
    {
        parentImage->setSensitivity(value);
    }
}

void DisplayImage::filter(QVector<bool> filter)
{

}
