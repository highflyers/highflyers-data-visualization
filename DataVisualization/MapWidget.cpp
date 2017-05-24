#include "MapWidget.h"
#include "QDebug"

#include <QPainter>

MapWidget::MapWidget(QWidget *parent) : QWidget(parent)
{
    label = new QLabel(this);
    label->setScaledContents(true);
}

void MapWidget::resizeEvent(QResizeEvent *event)
{
    qDebug() << "ResizeEvent" << event->size().width();
    this->w = event->size().width();
    this->h = event->size().height();
    label->setMinimumHeight(h);
    label->setMaximumHeight(h);
    label->setMinimumWidth(w);
    label->setMaximumWidth(w);
    QWidget::resizeEvent(event);
}

void MapWidget::updateImage(const QImage &displayImage)
{
    this->displayImage = displayImage;
    redrawContents();
}

void MapWidget::redrawContents()
{
    QImage resultImage = QImage(w, h, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&resultImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, displayImage.scaled(w, h));
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.fillRect(resultImage.rect(), Qt::white);
    painter.end();

    this->label->setPixmap(QPixmap::fromImage(resultImage));
}

int MapWidget::height() const
{
    return h;
}

int MapWidget::width() const
{
    return w;
}

void MapWidget::setPixmap(const QPixmap &pixmap)
{
    this->label->setPixmap(pixmap);
}
