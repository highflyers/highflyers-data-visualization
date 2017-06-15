#ifndef CURRENTLOCATIONOVERLAY_H
#define CURRENTLOCATIONOVERLAY_H

#include <qcustomplot.h>
#include <MapImageManipulation/MapOverlay.h>

class CurrentLocationOverlay : public MapOverlay
{
    Q_OBJECT
public:
    CurrentLocationOverlay(DisplayImage *parentImage, int droneId);
    ~CurrentLocationOverlay();
    QImage toImage();

private:
    int droneId = 0;
    QCustomPlot *customPlot;
    QCPCurve *plotCurve;
    QCPItemText *plotText;
    QVector<QCPCurveData> plotData;

public slots:
    void processData(const Message &message);
};

#endif // CURRENTLOCATIONOVERLAY_H
