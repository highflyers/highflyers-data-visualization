#include "MapFragment.h"

MapFragment::MapFragment(QObject *parent) : DisplayImage(parent)
{

}

QImage MapFragment::processData(const Message &message)
{
    return this->image;
}

QPair<QGeoCoordinate, QGeoCoordinate> MapFragment::limits() const
{
    return m_limits;
}
