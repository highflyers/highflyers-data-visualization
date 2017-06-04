#include "MapFragment.h"
#include <QDebug>

MapFragment::MapFragment(QObject *parent) : DisplayImage(parent)
{

}

QImage MapFragment::processData(const Message &message)
{
    qDebug();
    return this->image;
}

QPair<QGeoCoordinate, QGeoCoordinate> MapFragment::limits() const
{
    return m_limits;
}
