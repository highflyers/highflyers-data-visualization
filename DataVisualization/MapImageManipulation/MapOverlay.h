#ifndef MAPOVERLAY_H
#define MAPOVERLAY_H

#include <QObject>
#include <QImage>
#include <QColor>

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
    static QColor colorOf(int id);

public slots:
    virtual void processData(const Message &message);

protected:
    virtual int absoluteLongitudeToRelative(QGeoCoordinate position);
    virtual int absoluteLatitudeToRelative(QGeoCoordinate position);
};

#endif // MAPOVERLAY_H
