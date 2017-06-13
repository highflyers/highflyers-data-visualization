#ifndef DOTOVERLAY_H
#define DOTOVERLAY_H

#include <qcustomplot.h>
#include <MapImageManipulation/MapOverlay.h>

class DotOverlay : public MapOverlay
{
    Q_OBJECT
public:
    DotOverlay(DisplayImage *parentImage, BeaconColor beaconColor);
    ~DotOverlay();

    QImage toImage();
    void reset();

private:
    QCustomPlot *customPlot;
    QCPColorMap *colorMap;
    QCPColorScale *colorScale;
    QCPMarginGroup *marginGroup;
    BeaconColor beaconColor;
    double colorMapMax;
    double colorMapMin;

    double rssiNorm(int rssi);
    double distance(int x0, int y0, int x1, int y1);

public slots:
    void processData(const Message &message);
    QImage rewriteImage();
};

#endif // DOTOVERLAY_H
