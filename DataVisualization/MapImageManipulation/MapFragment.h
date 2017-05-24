#ifndef MAPFRAGMENT_H
#define MAPFRAGMENT_H

#include <QObject>
#include <QPair>
#include <QtPositioning/QGeoCoordinate>
#include <QImage>

/**
 * @brief Structure containing map image and info
 */
class MapFragment : public QObject
{
    Q_OBJECT
public:
    QPair<QGeoCoordinate, QGeoCoordinate> limits;
    QImage image;
};

#endif // MAPFRAGMENT_H
