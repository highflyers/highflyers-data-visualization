#ifndef MAPOVERLAY_H
#define MAPOVERLAY_H

#include <QObject>
#include <QImage>

#include <Message.h>

/**
 * @brief Interface for map overlays
 */
class MapOverlay : public QObject
{
    Q_OBJECT
public:
    explicit MapOverlay(QObject *parent = 0): QObject(parent) {}
    virtual ~MapOverlay() {}

    virtual QImage toImage() = 0;

signals:

public slots:
    virtual void processData(const Message &message) = 0;
};

#endif // MAPOVERLAY_H
