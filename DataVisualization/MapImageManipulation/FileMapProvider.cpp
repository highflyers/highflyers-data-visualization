#include "FileMapProvider.h"
#include <QDebug>
#include <QSettings>
#include <QDir>

FileMapProvider::FileMapProvider(const QString &imageFile, const QString &descriptionFile, QObject *parent) : MapProvider(parent)
{
    QString imageFilename;
    double lat1, lat2, lon1, lon2;
    QSettings* settings = new QSettings(descriptionFile, QSettings::IniFormat);
    bool readSuccessfull = true;
    lat1 = settings->value("lat1").toDouble(&readSuccessfull);
    lat2 = settings->value("lat2").toDouble(&readSuccessfull);
    lon1 = settings->value("lon1").toDouble(&readSuccessfull);
    lon2 = settings->value("lon2").toDouble(&readSuccessfull);
    imageFilename = settings->value("file").toString();

    delete settings;

    limits.first.setLatitude(lat1);
    limits.first.setLongitude(lon1);
    limits.second.setLatitude(lat2);
    limits.second.setLongitude(lon2);

    QDir d = QFileInfo(descriptionFile).absoluteDir();

    mapImagePixmap = new QPixmap(d.absoluteFilePath(imageFilename));
}

FileMapProvider::~FileMapProvider()
{
    delete mapImagePixmap;
}

MapFragment* FileMapProvider::getImage(QPair<QGeoCoordinate, QGeoCoordinate> limits)
{
    MapFragment *fragment = new MapFragment();
    fragment->image = mapImagePixmap->toImage();
    fragment->m_limits = this->limits;
    qDebug() << fragment->limits().first.toString() << fragment->limits().second.toString();
    return fragment;
}
