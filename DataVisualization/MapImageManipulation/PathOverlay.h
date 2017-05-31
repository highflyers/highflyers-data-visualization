#ifndef PATHOVERLAY_H
#define PATHOVERLAY_H

#include <qcustomplot.h>
#include <MapImageManipulation/MapOverlay.h>

class PathOverlay : public MapOverlay
{
    Q_OBJECT
public:
    PathOverlay(DisplayImage *parentImage, QObject *parent = 0);
    ~PathOverlay();
    QPair<QGeoCoordinate, QGeoCoordinate> limits() const;
    QImage toImage();

private:
    DisplayImage *parentImage;
    unsigned width, height;
    QCustomPlot *customPlot;
    QCPCurve *pathCurve;
    QVector<QCPCurveData> pathData;

    int absoluteLongitudeToRelative(QGeoCoordinate position);
    int absoluteLatitudeToRelative(QGeoCoordinate position);

signals:

public slots:
    QImage processData(const Message &message);
};

#endif // PATHOVERLAY_H
