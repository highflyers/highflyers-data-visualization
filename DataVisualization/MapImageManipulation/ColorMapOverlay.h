#ifndef COLORMAPOVERLAY_H
#define COLORMAPOVERLAY_H

#include <QObject>

#include <MapImageManipulation/MapOverlay.h>
#include <qcustomplot.h>

class ColorMapOverlay : public MapOverlay
{
    Q_OBJECT
public:
    explicit ColorMapOverlay(QObject *parent = 0);
    ColorMapOverlay(unsigned width, unsigned height, QObject *parent = 0);
    ~ColorMapOverlay();

    QImage toImage();

private:
    QCustomPlot *customPlot;
    QCPColorMap *colorMap;
    QCPColorScale *colorScale;
    QCPMarginGroup *marginGroup;
    unsigned width, height;

signals:

public slots:
    void processData(const Message &message);

};

#endif // COLORMAPOVERLAY_H
