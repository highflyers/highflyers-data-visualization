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
    explicit DisplayImage(QObject *parent = 0);
    virtual ~DisplayImage(){}

    virtual QPair<QGeoCoordinate, QGeoCoordinate> limits() const = 0;
    QImage image;

    double getWidth();
    double getHeight();

signals:

public slots:
    virtual QImage processData(const Message &message) = 0;
};

#endif // DISPLAYIMAGE_H
