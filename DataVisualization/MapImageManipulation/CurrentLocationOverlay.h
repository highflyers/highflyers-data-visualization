//#ifndef CURRENTLOCATIONOVERLAY_H
//#define CURRENTLOCATIONOVERLAY_H

//#include <qcustomplot.h>
//#include <MapImageManipulation/MapOverlay.h>

//class CurrentLocationOverlay : public MapOverlay
//{
//    Q_OBJECT
//public:
//    CurrentLocationOverlay(DisplayImage *parentImage, QObject *parent = 0);
//    ~CurrentLocationOverlay();
//    QPair<QGeoCoordinate, QGeoCoordinate> limits() const;
//    QImage toImage();

//private:
//    DisplayImage *parentImage;
//    unsigned width, height;
//    QCustomPlot *customPlot;
//    QCPCurve *pathCurve;
//    QVector<QCPCurveData> pathData;

//    int absoluteLongitudeToRelative(QGeoCoordinate position);
//    int absoluteLatitudeToRelative(QGeoCoordinate position);

//signals:

//public slots:
//    void processData(const Message &message);
//    QImage rewriteImage();
//};

//#endif // CURRENTLOCATIONOVERLAY_H
