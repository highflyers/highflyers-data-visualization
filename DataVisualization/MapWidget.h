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

    void resizeEvent(QResizeEvent *event);

signals:
    void pointSelected(const QGeoCoordinate &point);

public slots:
    void updateImage(const DisplayImage *displayImage);

private:
    int h, w;
    QPair<QGeoCoordinate, QGeoCoordinate> mapLimits;
    QGeoCoordinate relativeToAbsolute(double x, double y);

    void updateImage(const QImage& displayImage);

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // MAPWIDGET_H
