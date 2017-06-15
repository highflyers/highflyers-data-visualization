#include <MapImageManipulation/MapOverlay.h>

MapOverlay::MapOverlay(DisplayImage *parent) : DisplayImage(parent)
{
}

QColor MapOverlay::colorOf(int id)
{
    id = id % 3;
    switch (id) {
    case 0:
        return QColor(0,0,0,127);
        break;
    case 1:
        return QColor(0,0,255,127);
        break;
    case 2:
        return QColor(255,0,255,127);
    default:
        break;
    }
}

void MapOverlay::processData(const Message &message)
{
    parentImage->processData(message);
}

int MapOverlay::absoluteLongitudeToRelative(QGeoCoordinate position)
{
    QPair<QGeoCoordinate, QGeoCoordinate> limits = this->limits();
    int result = -1;
    if(position.longitude() > limits.first.longitude() && position.longitude() < limits.second.longitude())
        result = static_cast<int>(getWidth()/(limits.second.longitude() - limits.first.longitude()) * (position.longitude() - limits.first.longitude()));

    return result;
}

int MapOverlay::absoluteLatitudeToRelative(QGeoCoordinate position)
{
    QPair<QGeoCoordinate, QGeoCoordinate> limits = this->limits();
    int result = -1;
    double unit = getHeight()/(limits.second.latitude() - limits.first.latitude());
    if(position.latitude() > limits.first.latitude() && position.latitude() < limits.second.latitude())
        result = static_cast<int>((position.latitude() - limits.first.latitude()) * unit);

    return result;
}

