#ifndef PATHOVERLAY_H
#define PATHOVERLAY_H

#include <qcustomplot.h>
#include <MapImageManipulation/MapOverlay.h>

class PathOverlay : public MapOverlay
{
    Q_OBJECT
public:
    PathOverlay(DisplayImage *parentImage);
    ~PathOverlay();
    QImage toImage();

private:
    QCustomPlot *customPlot;
    QCPCurve *pathCurve;
    QVector<QCPCurveData> pathData;

public slots:
    void processData(const Message &message);
    QImage rewriteImage();
};

#endif // PATHOVERLAY_H
