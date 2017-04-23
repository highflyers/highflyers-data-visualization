#ifndef FILEMAPPROVIDER_H
#define FILEMAPPROVIDER_H

#include <MapProvider.h>
#include <QString>
#include <QPixmap>

/**
 * @brief Implementation of MapProvider that uses local files for map generation.
 */
class FileMapProvider : public MapProvider
{
public:
    /**
     * @brief FileMapProvider
     * @param imageFile
     * @param descriptionFile
     */
    FileMapProvider(const QString &imageFile, const QString &descriptionFile, QObject *parent = 0);

    ~FileMapProvider();

    QSharedPointer<MapFragment> getImage(QPair<QGeoCoordinate, QGeoCoordinate> limits);

private:
    QPixmap *mapImagePixmap;
};

#endif // FILEMAPPROVIDER_H
