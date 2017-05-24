#ifndef MAPOVERLAY_H
#define MAPOVERLAY_H

#include <QObject>
#include <QImage>

#include <Message.h>
#include <MapImageManipulation/DisplayImage.h>

/**
 * @brief Interface for map overlays
 */
class MapOverlay : public DisplayImage
{
    Q_OBJECT
public:
    explicit MapOverlay(QObject *parent = 0) : DisplayImage(parent) {}
    virtual ~MapOverlay() {}

    virtual QImage toImage() = 0;
signals:

public slots:
    virtual QImage processData(const Message &message) = 0;
};

#endif // MAPOVERLAY_H
