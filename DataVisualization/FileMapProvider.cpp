#include "FileMapProvider.h"

FileMapProvider::FileMapProvider(const QString &imageFile, const QString &descriptionFile, QObject *parent) : MapProvider(parent)
{
    mapImagePixmap = new QPixmap(imageFile);
}

FileMapProvider::~FileMapProvider()
{
    delete mapImagePixmap;
}

QSharedPointer<MapFragment> FileMapProvider::getImage(QPair<QGeoCoordinate, QGeoCoordinate> limits)
{
    MapFragment *fragment = new MapFragment();
    fragment->image = mapImagePixmap->toImage();
    return QSharedPointer<MapFragment>(fragment);
}
