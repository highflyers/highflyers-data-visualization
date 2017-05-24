#include "MapWidget.h"
#include "QDebug"

#include <QPainter>
#include <QMessageLogger>

MapWidget::MapWidget(QWidget *parent) : QLabel(parent)
{
    this->setScaledContents(true);
    // TODO: remove when map begins to provide real data
    this->mapLimits.first = QGeoCoordinate(1,1,0);
    this->mapLimits.second = QGeoCoordinate(2,2,0);
}

void MapWidget::resizeEvent(QResizeEvent *event)
{
    qDebug() << event->size().width();
    this->w = event->size().width();
    this->h = event->size().height();
    QLabel::resizeEvent(event);
}

void MapWidget::updateOverlay(const QImage &overlay)
{
    qDebug();
    this->overlay = overlay;
    redrawContents();
}

void MapWidget::updatePath(const QImage &path)
{
    qDebug();
    this->path = path;
    redrawContents();
}

void MapWidget::updateImage(const MapFragment &map)
{
    this->setPixmap(QPixmap::fromImage(map.image));
    this->mapLimits = map.limits;
}

void MapWidget::redrawContents()
{
    if(!path.isNull() && !overlay.isNull()){
    qDebug();
    QPainter::CompositionMode mode = QPainter::CompositionMode_Multiply;

    QImage resultImage = QImage(w, h, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&resultImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, overlay.scaled(w, h));
    painter.setCompositionMode(mode);
    painter.drawImage(0, 0, path.scaled(w, h));
    painter.setCompositionMode(mode);
    painter.drawImage(0, 0, (*mapImage).scaled(w, h));
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.fillRect(resultImage.rect(), Qt::white);
    painter.end();

    this->setPixmap(QPixmap::fromImage(resultImage));
    }
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

void MapWidget::setMap(const QImage &newMapImage)
{
    if(mapImage != nullptr) delete mapImage;
    this->mapImage = new QImage(newMapImage);
}
