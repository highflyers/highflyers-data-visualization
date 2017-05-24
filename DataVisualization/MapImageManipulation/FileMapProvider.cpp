#include "FileMapProvider.h"
#include <QDebug>

FileMapProvider::FileMapProvider(const QString &imageFile, const QString &descriptionFile, QObject *parent) : MapProvider(parent)
{
    mapImagePixmap = new QPixmap(imageFile);
}

FileMapProvider::~FileMapProvider()
{
    delete mapImagePixmap;
}

MapFragment* FileMapProvider::getImage(QPair<QGeoCoordinate, QGeoCoordinate> limits)
{
    MapFragment *fragment = new MapFragment();
    fragment->image = mapImagePixmap->toImage();
    fragment->m_limits = limits;
    qDebug() << fragment->limits().first.toString() << fragment->limits().second.toString();
    return fragment;
}
