#ifndef MAPFRAGMENT_H
#define MAPFRAGMENT_H

#include <QObject>
#include <MapImageManipulation/DisplayImage.h>

class FileMapProvider;

/**
 * @brief Structure containing map image and info
 */
class MapFragment : public DisplayImage
{
    Q_OBJECT
    friend class FileMapProvider;
public:
    explicit MapFragment(QObject *parent = 0);
    ~MapFragment(){}
    void processData(const Message &message);
    QImage rewriteImage();
    QPair<QGeoCoordinate, QGeoCoordinate> limits() const;
    QImage toImage();

    unsigned getWidth();
    unsigned getHeight();

private:
    QPair<QGeoCoordinate, QGeoCoordinate> m_limits;
};

#endif // MAPFRAGMENT_H

