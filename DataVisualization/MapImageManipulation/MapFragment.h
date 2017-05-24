#ifndef MAPFRAGMENT_H
#define MAPFRAGMENT_H

#include <QObject>
#include <MapImageManipulation/DisplayImage.h>

/**
 * @brief Structure containing map image and info
 */
class MapFragment : public DisplayImage
{
    Q_OBJECT
public:
    explicit MapFragment(QObject *parent = 0);
    QImage processData(const Message &message);
};

#endif // MAPFRAGMENT_H

