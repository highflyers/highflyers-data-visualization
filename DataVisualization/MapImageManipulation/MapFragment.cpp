#include "MapFragment.h"
#include <QDebug>

MapFragment::MapFragment(QObject *parent) : DisplayImage(parent)
{

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
