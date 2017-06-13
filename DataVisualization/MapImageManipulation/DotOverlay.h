#ifndef DOTOVERLAY_H
#define DOTOVERLAY_H

#include <qcustomplot.h>
#include <MapImageManipulation/MapOverlay.h>

class DotOverlay : public MapOverlay
{
    Q_OBJECT
public:
    explicit DotOverlay(QObject *parent = 0);
    DotOverlay(DisplayImage *parentImage, BeaconColor beaconColor, QObject *parent = 0);
    ~DotOverlay();

    QPair<QGeoCoordinate, QGeoCoordinate> limits() const;

    QImage toImage();

private:
    DisplayImage *parentImage;
    QCustomPlot *customPlot;
    QCPColorMap *colorMap;
    QCPColorScale *colorScale;
    QCPMarginGroup *marginGroup;
    unsigned width, height;
    BeaconColor beaconColor;
    double colorMapMax;
    double colorMapMin;

    int absoluteLatitudeToRelative(QGeoCoordinate position);
    int absoluteLongitudeToRelative(QGeoCoordinate position);

    double rssiNorm(int rssi);
    double distance(int x0, int y0, int x1, int y1);
signals:

public slots:
    void processData(const Message &message);
    QImage rewriteImage();
};

#endif // DOTOVERLAY_H
