#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QResizeEvent>
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QGeoCoordinate>

#include <MapImageManipulation/MapFragment.h>

/**
 * @brief A widget responsible for displaying a map (as QImage).
 */
class MapWidget : public QLabel
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget *parent = 0);

    int height() const;
    int width() const;

    void setMap(const QImage &newMapImage); // to be removed in next version

    void resizeEvent(QResizeEvent *event);

signals:
    void pointSelected(const QGeoCoordinate &point);

public slots:
    void updateOverlay(const QImage &overlay); // to be removed in next version
    void updatePath(const QImage &path); // to be removed in next version
    void updateImage(const MapFragment &map);

private:
    int h, w;
    QPixmap *mapImagePixmap = nullptr;
    QImage *mapImage = nullptr;
    QImage overlay, path; // to be removed in next version
    void redrawContents(); // to be removed in next version
    QPair<QGeoCoordinate, QGeoCoordinate> mapLimits;
    QGeoCoordinate relativeToAbsolute(double x, double y);

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // MAPWIDGET_H
