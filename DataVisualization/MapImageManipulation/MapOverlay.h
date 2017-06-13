#ifndef MAPOVERLAY_H
#define MAPOVERLAY_H

#include <QObject>
#include <QImage>

#include <Message.h>
#include <MapImageManipulation/DisplayImage.h>

enum BeaconColor{
    green = 0,
    red = 1,
    yellow = 2,
    black = 3
};

/**
 * @brief Interface for map overlays
 */
class MapOverlay : public DisplayImage
{
    Q_OBJECT
public:
    MapOverlay(DisplayImage *parent);
    virtual ~MapOverlay() {}

signals:

public slots:
    virtual void processData(const Message &message) = 0;
    virtual QImage rewriteImage() = 0;

protected:
    int absoluteLongitudeToRelative(QGeoCoordinate position);
    int absoluteLatitudeToRelative(QGeoCoordinate position);
};

#endif // MAPOVERLAY_H
