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
    void setSensitivity(double value);

private:
    QCustomPlot *customPlot;
    QCPColorMap *colorMap;
    QCPColorScale *colorScale;
    QCPMarginGroup *marginGroup;
    BeaconColor beaconColor;
    double colorMapMax;
    double colorMapMin;
    double sensitivity = 1.0;
    const double SENSITIVITY_OFFSET = 10;

    double rssiNorm(int rssi);
    double distance(int x0, int y0, int x1, int y1);

    double calculateWithSensitivity(double power);
    void calculateWithSensitivityAllCells();

public slots:
    void processData(const Message &message);
    QImage rewriteImage();
};

#endif // DOTOVERLAY_H
