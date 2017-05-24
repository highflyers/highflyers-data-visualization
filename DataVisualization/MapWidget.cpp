#include "MapWidget.h"
#include "QDebug"

#include <QPainter>
#include <QMessageLogger>

MapWidget::MapWidget(QWidget *parent) : QLabel(parent)
{
    this->setScaledContents(true);
}

void MapWidget::resizeEvent(QResizeEvent *event)
{
    qDebug() << event->size().width();
    this->w = event->size().width();
    this->h = event->size().height();
    QLabel::resizeEvent(event);
}

void MapWidget::updateImage(const DisplayImage *displayImage)
{
    qDebug() << displayImage->limits().first.toString();
    updateImage(displayImage->image);
    this->mapLimits = displayImage->limits();
}

void MapWidget::updateImage(const QImage &displayImage)
{
    qDebug();
    this->setPixmap(QPixmap::fromImage(displayImage.scaled(w, h)));
}

QGeoCoordinate MapWidget::relativeToAbsolute(double x, double y)
{
    double absX = mapLimits.first.longitude() + x * (mapLimits.second.longitude() - mapLimits.first.longitude());
    double absY = mapLimits.first.latitude() + y * (mapLimits.second.latitude() - mapLimits.first.latitude());
    QGeoCoordinate ret(absX, absY, 0);
    qDebug() << "Relative position = (" << x << y << ") -> absolute position = " << ret.toString();
    return ret;
}

void MapWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Clicked in point: " << event->pos() << "widget size is " << width() << "x" << height();
    double relX = (double)event->pos().x() / (double)width();
    double relY = (double)event->pos().y() / (double)height();
    emit pointSelected(relativeToAbsolute(relX, relY));
}

int MapWidget::height() const
{
    return h;
}

int MapWidget::width() const
{
    return w;
}
