#ifndef COLORMAPOVERLAY_H
#define COLORMAPOVERLAY_H

#include <QObject>

#include <MapImageManipulation/MapOverlay.h>
#include <MapImageManipulation/DisplayImage.h>
#include <qcustomplot.h>
#include <MapImageManipulation/MapOverlay.h>


enum BeaconColor{
    green = 0,
    red = 1,
    yellow = 2,
    black = 3
};

class ColorMapOverlay : public MapOverlay
{
    Q_OBJECT
public:
    explicit ColorMapOverlay(QObject *parent = 0);
    ColorMapOverlay(DisplayImage *parentImage, BeaconColor beaconColor, QObject *parent = 0);
    ~ColorMapOverlay();

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
signals:

public slots:
    void processData(const Message &message);
    QImage rewriteImage();

};

#endif // COLORMAPOVERLAY_H
