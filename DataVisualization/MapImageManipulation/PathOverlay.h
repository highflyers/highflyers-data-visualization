#ifndef PATHOVERLAY_H
#define PATHOVERLAY_H

#include <qcustomplot.h>
#include <MapImageManipulation/MapOverlay.h>

class PathOverlay : public MapOverlay
{
    Q_OBJECT
public:
    PathOverlay(DisplayImage *parentImage, int droneId);
    ~PathOverlay();
    QImage toImage();
    void reset();

private:
    QCustomPlot *customPlot;
    QCPCurve *pathCurve;
    QVector<QCPCurveData> pathData;
    int droneId = 0;

public slots:
    void processData(const Message &message);
};

#endif // PATHOVERLAY_H
