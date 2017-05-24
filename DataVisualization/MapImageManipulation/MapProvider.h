#ifndef MAPPROVIDER_H
#define MAPPROVIDER_H

#include <QObject>
#include <QImage>
#include <QSharedPointer>
#include <QPair>
#include <QtPositioning/QGeoCoordinate>

#include <MapImageManipulation/MapFragment.h>

/**
 * @brief An interface for all map provider classes.
 *
 * It is responsible for coreation of MapFragment objects.
 */
class MapProvider : public QObject
{
    Q_OBJECT
public:
    explicit MapProvider(QObject *parent = 0) : QObject(parent) {}
    virtual ~MapProvider() {}

    /**
     * @brief Returns a map representing the area contained in limits
     * @param limits: a pair of coordinates, where first element is NW corner of a map and second element is SE corner
     * @note Returned map can cover an area larger than the one constrained by limits
     * @todo Verify this idea
     */
    virtual MapFragment *getImage(QPair<QGeoCoordinate, QGeoCoordinate> limits) = 0;

signals:

public slots:
};

#endif // MAPPROVIDER_H
