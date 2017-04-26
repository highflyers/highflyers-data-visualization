#ifndef PATHOVERLAY_H
#define PATHOVERLAY_H

#include <qcustomplot.h>
#include <MapImageManipulation/MapOverlay.h>

class PathOverlay : public MapOverlay
{
    Q_OBJECT
public:
    PathOverlay(unsigned width, unsigned height, QObject *parent = 0);

    QImage toImage();

private:
    unsigned width, height;
    QCustomPlot *customPlot;
    QCPCurve *pathCurve;

signals:

public slots:
    void processData(const Message &message);
};

#endif // PATHOVERLAY_H
