#ifndef DISPLAYIMAGE_H
#define DISPLAYIMAGE_H

#include <QObject>
#include <QPair>
#include <QtPositioning/QGeoCoordinate>
#include <QImage>
#include <Message.h>

class DisplayImage : public QObject
{
    Q_OBJECT
public:
    QImage image;

    explicit DisplayImage(DisplayImage *parentImage);
    virtual ~DisplayImage(){}

    virtual QPair<QGeoCoordinate, QGeoCoordinate> limits() const;

    virtual unsigned getWidth();
    virtual unsigned getHeight();

public slots:
    virtual void processData(const Message &message) = 0;
    virtual QImage rewriteImage();
    virtual void reset();
    virtual void setSensitivity(double value);

protected:
    DisplayImage *parentImage;

    virtual QImage toImage() = 0;
};

#endif // DISPLAYIMAGE_H
