#include "MapFragment.h"
#include <QDebug>

MapFragment::MapFragment(QObject *parent) : DisplayImage(nullptr)
{

}

unsigned MapFragment::getWidth()
{
    return image.width();
}

unsigned MapFragment::getHeight()
{
    return image.height();
}

void MapFragment::processData(const Message &message)
{
    qDebug();
}

QImage MapFragment::rewriteImage()
{
    return this->image;
}

QPair<QGeoCoordinate, QGeoCoordinate> MapFragment::limits() const
{
    return m_limits;
}

QImage MapFragment::toImage()
{
    qDebug() << getWidth() << getHeight();
    return rewriteImage();
}
