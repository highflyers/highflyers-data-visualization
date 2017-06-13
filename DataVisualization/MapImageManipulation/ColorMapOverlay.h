#ifndef COLORMAPOVERLAY_H
#define COLORMAPOVERLAY_H

#include <QObject>

#include <MapImageManipulation/MapOverlay.h>
#include <MapImageManipulation/DisplayImage.h>
#include <qcustomplot.h>
#include <MapImageManipulation/MapOverlay.h>

class ColorMapOverlay : public MapOverlay
{
    Q_OBJECT
public:
    ColorMapOverlay(DisplayImage *parentImage, BeaconColor beaconColor);
    ~ColorMapOverlay();

    QImage toImage();

private:
    QCustomPlot *customPlot;
    QCPColorMap *colorMap;
    QCPColorScale *colorScale;
    QCPMarginGroup *marginGroup;
    BeaconColor beaconColor;
    double colorMapMax;
    double colorMapMin;

public slots:
    void processData(const Message &message);
    QImage rewriteImage();

};

#endif // COLORMAPOVERLAY_H
