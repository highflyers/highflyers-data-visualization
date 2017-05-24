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
    explicit ColorMapOverlay(QObject *parent = 0);
    ColorMapOverlay(DisplayImage *parentImage, QObject *parent = 0);
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

signals:

public slots:
    QImage processData(const Message &message);

};

#endif // COLORMAPOVERLAY_H
