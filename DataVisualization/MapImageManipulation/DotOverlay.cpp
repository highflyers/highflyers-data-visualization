#include "DotOverlay.h"
#include <QDebug>

DotOverlay::DotOverlay(QObject *parent) : MapOverlay(parent)
{
}

DotOverlay::DotOverlay(DisplayImage *parentImage, BeaconColor beaconColor, QObject* parent) : MapOverlay(parent), beaconColor(beaconColor), parentImage(parentImage)
{
    customPlot = new QCustomPlot();
    customPlot->axisRect()->setAutoMargins(QCP::msNone);
    customPlot->axisRect()->setMargins(QMargins(0,0,0,0));

    colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
    colorMap->data()->setSize(parentImage->getWidth(), parentImage->getHeight());
    colorMap->data()->setRange(QCPRange(0, 8), QCPRange(0, 8));

    image = parentImage->image;
    width = parentImage->getWidth();
    height = parentImage->getHeight();

    colorScale = new QCPColorScale(customPlot);
    colorMap->setColorScale(colorScale);
    QCPColorGradient *gradient;
    switch(this->beaconColor){
        case green:
            gradient = new QCPColorGradient();
            gradient->setColorStopAt(0, QColor(0,255,0,0));
            gradient->setColorStopAt(0.2, QColor(0,255,0,127));
            gradient->setColorStopAt(1, QColor(0,255,0,255));
            colorMap->setGradient(gradient->inverted());
            break;
        case red:
            gradient = new QCPColorGradient();
            gradient->setColorStopAt(0, QColor(255,0,0,0));
            gradient->setColorStopAt(0.2, QColor(255,0,0,127));
            gradient->setColorStopAt(1, QColor(255,0,0,255));
            colorMap->setGradient(gradient->inverted());
            break;
        case yellow:
            gradient = new QCPColorGradient();
            gradient->setColorStopAt(0, QColor(255,200,0,0));
            gradient->setColorStopAt(0.2, QColor(255,150,0,127));
            gradient->setColorStopAt(1, QColor(255,200,0,255));
            colorMap->setGradient(gradient->inverted());
            break;
        case black:
            gradient = new QCPColorGradient();
            gradient->setColorStopAt(0, QColor(0,0,0,0));
            gradient->setColorStopAt(0.5, QColor(0,0,0,127));
            gradient->setColorStopAt(1, QColor(0,0,0,255));
            colorMap->setGradient(gradient->inverted());
            break;
        default:
            gradient = new QCPColorGradient(QCPColorGradient::gpThermal);
            colorMap->setGradient(*gradient);
            break;
    }

//    QCPColorGradient gradient(QCPColorGradient::gpThermal);
//    colorMap->setGradient(gradient.inverted());

    for (unsigned xIndex = 0; xIndex < parentImage->getWidth(); xIndex += 1)
    {
        for (unsigned yIndex = 0; yIndex < parentImage->getHeight(); yIndex += 1)
        {
            colorMap->data()->setCell(xIndex, yIndex, 1.0);
        }
    }

    colorMapMax = 1.0;
    colorMapMin = 0.0;
    customPlot->rescaleAxes();
}

DotOverlay::~DotOverlay()
{
    delete customPlot;
    delete colorMap;
    delete colorScale;
    delete marginGroup;
    delete parentImage;
}

QPair<QGeoCoordinate, QGeoCoordinate> DotOverlay::limits() const
{
    return parentImage->limits();
}

QImage DotOverlay::toImage()
{
    QPixmap mapPixmap = customPlot->toPixmap(width, height);
    return mapPixmap.toImage();
}

int DotOverlay::absoluteLongitudeToRelative(QGeoCoordinate position)
{
    QPair<QGeoCoordinate, QGeoCoordinate> limits = this->limits();
    int result = -1;
    if(position.longitude() > limits.first.longitude() && position.longitude() < limits.second.longitude())
        result = static_cast<int>(width/(limits.second.longitude() - limits.first.longitude()) * (position.longitude() - limits.first.longitude()));

    return result;
}

double DotOverlay::rssiNorm(int rssi)
{
    if(rssi == -200)
    {
        return -1.0;
    }
    else
    {
        return 1.0-((rssi + 200.0) / 150.0);
    }
}

double DotOverlay::distance(int x0, int y0, int x1, int y1)
{
    double p1 = x1 - x0;
    p1 = p1 * p1;
    double p2 = y1 - y0;
    p2 = p2 * p2;
    return qSqrt(p1 + p2);
}

int DotOverlay::absoluteLatitudeToRelative(QGeoCoordinate position)
{
    QPair<QGeoCoordinate, QGeoCoordinate> limits = this->limits();
    int result = -1;
    double unit = height/(limits.second.latitude() - limits.first.latitude());
    if(position.latitude() > limits.first.latitude() && position.latitude() < limits.second.latitude())
        result = static_cast<int>((position.latitude() - limits.first.latitude()) * unit);

    return result;
}

void DotOverlay::processData(const Message &message)
{
    qDebug();
    /// @todo Implement operations
    parentImage->processData(message);
    width = image.width();
    height = image.height();

    int x=0;
    int y=0;

    if((x = absoluteLongitudeToRelative(message.position)) != -1){
        qDebug() << "x: " << x;
        if((y = absoluteLatitudeToRelative(message.position)) != -1){
            qDebug() << "y: " << y;

            auto it = message.data.begin();
            switch(beaconColor){
                case green:
                    it+=0;
                    break;
                case red:
                    it+=1;
                    break;
                case yellow:
                    it+=2;
                    break;
                case black:
                    it+=3;
                    break;
            }
            auto end_it = it+1;
            for(it; it!=end_it; ++it){
                int rssi = *it;
                double power = rssiNorm(rssi);
                if(power>0){
                    int radius = 0.01 * qMin(width, height);
                    qDebug() << "power" << power;
                    for(int ix = qMax(0, x - radius); ix < qMin((int)width, x + radius); ++ix)
                    {
                        for(int iy = qMax(0, y - radius); iy < qMin((int)width, y + radius); ++iy)
                        {
                            if(distance(x,y,ix,iy) < radius)
                            {
                                colorMap->data()->setCell(ix, iy, qMin(colorMap->data()->cell(ix, iy), power));
                            }
                        }
                    }
                }
            }
        }
    }
}

QImage DotOverlay::rewriteImage()
{
    image = parentImage->rewriteImage();

    colorMap->setDataRange(QCPRange(colorMapMin, colorMapMax));

    QImage overlayImage = this->toImage();

    QPainter::CompositionMode mode = QPainter::CompositionMode_Multiply;

    QImage resultImage = QImage(width, height, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&resultImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, overlayImage.scaled(width, height));
    painter.setCompositionMode(mode);
    painter.drawImage(0, 0, image.scaled(width, height));
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.fillRect(resultImage.rect(), Qt::white);
    painter.end();

    image = resultImage;

    return image;
}
