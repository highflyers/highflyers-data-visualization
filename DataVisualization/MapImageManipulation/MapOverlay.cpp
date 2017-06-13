#include <MapImageManipulation/MapOverlay.h>

MapOverlay::MapOverlay(DisplayImage *parent) : DisplayImage(parent)
{
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
