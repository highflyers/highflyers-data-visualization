#include "ColorMapOverlay.h"

ColorMapOverlay::ColorMapOverlay(QObject *parent) : MapOverlay(parent)
{
}

ColorMapOverlay::ColorMapOverlay(DisplayImage *parentImage, BeaconColor beaconColor, QObject* parent) : MapOverlay(parent), beaconColor(beaconColor), parentImage(parentImage)
{
    customPlot = new QCustomPlot();
    customPlot->axisRect()->setAutoMargins(QCP::msNone);
    customPlot->axisRect()->setMargins(QMargins(0,0,0,0));

    colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
    colorMap->data()->setSize(parentImage->getWidth(), parentImage->getHeight());
    colorMap->data()->setRange(QCPRange(0, 8), QCPRange(0, 8));

    image = parentImage->image;

    colorScale = new QCPColorScale(customPlot);
    colorMap->setColorScale(colorScale);
    QCPColorGradient *gradient;
    switch(this->beaconColor){
        case green:
            gradient = new QCPColorGradient();
            gradient->setColorStopAt(0, QColor(116,158,0,0));
            gradient->setColorStopAt(0.1, QColor(116,158,0,127));
            gradient->setColorStopAt(1, QColor(16,31,0,255));
            colorMap->setGradient(gradient->inverted());
            break;
        case red:
            gradient = new QCPColorGradient();
            gradient->setColorStopAt(0, QColor(255,0,4,0));
            gradient->setColorStopAt(0.1, QColor(255,0,4,127));
            gradient->setColorStopAt(1, QColor(115,0,2,255));
            colorMap->setGradient(gradient->inverted());
            break;
        case yellow:
            gradient = new QCPColorGradient();
            gradient->setColorStopAt(0, QColor(237,250,125,0));
            gradient->setColorStopAt(0.1, QColor(237,250,125,127));
            gradient->setColorStopAt(1, QColor(230,255,0,255));
            colorMap->setGradient(gradient->inverted());
            break;
        case black:
            gradient = new QCPColorGradient();
            gradient->setColorStopAt(0, QColor(183,184,176,0));
            gradient->setColorStopAt(0.1, QColor(183,184,176,127));
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
            colorMap->data()->setCell(xIndex, yIndex, 1);
        }
    }

    colorMapMax = 1.0;
    colorMapMin = 0.99;
    customPlot->rescaleAxes();
}

ColorMapOverlay::~ColorMapOverlay()
{
    delete customPlot;
    delete colorMap;
    delete colorScale;
    delete marginGroup;
    delete parentImage;
}

QPair<QGeoCoordinate, QGeoCoordinate> ColorMapOverlay::limits() const
{
    return parentImage->limits();
}

QImage ColorMapOverlay::toImage()
{
    QPixmap mapPixmap = customPlot->toPixmap(width, height);
    return mapPixmap.toImage();
}

int ColorMapOverlay::absoluteLongitudeToRelative(QGeoCoordinate position)
{
    QPair<QGeoCoordinate, QGeoCoordinate> limits = this->limits();
    int result = -1;
    if(position.longitude() > limits.first.longitude() && position.longitude() < limits.second.longitude())
        result = static_cast<int>(width/(limits.second.longitude() - limits.first.longitude()) * (position.longitude() - limits.first.longitude()));

    return result;
}

int ColorMapOverlay::absoluteLatitudeToRelative(QGeoCoordinate position)
{
    QPair<QGeoCoordinate, QGeoCoordinate> limits = this->limits();
    int result = -1;
    if(position.latitude() > limits.first.latitude() && position.latitude() < limits.second.latitude())
        result = static_cast<int>(width/(limits.second.latitude() - limits.first.latitude()) * (limits.second.latitude() - position.latitude()));

    return result;
}

QImage ColorMapOverlay::processData(const Message &message)
{
    /// @todo Implement operations
    image = parentImage->processData(message);
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
                    it+=4;
                    break;
                case yellow:
                    it+=8;
                    break;
                case black:
                    it+=12;
                    break;
            }
            auto end_it = it+4;
            for(it; it!=end_it; ++it){
                int radius = *it;
                if(radius>0){
                    for (unsigned xIndex = 0; xIndex < width; xIndex += 1)
                    {
                        for (unsigned yIndex = 0; yIndex < height; yIndex += 1)
                        {
                            double z;
                            int left = (xIndex-x)*(xIndex-x) + (yIndex-y)*(yIndex-y);
                            double eps = 0.125*radius*radius;
                            if(left <= radius*radius + eps && left >= radius*radius - eps)
                            {
                                z = colorMap->data()->cell(xIndex, yIndex) - 0.2;
                                z = qMax(z, 0.0);
                                colorMapMin = qMin(z,colorMapMin);
                                colorMap->data()->setCell(xIndex, yIndex, z);
                            }
                        }
                    }
//                    unsigned xIndex, yIndex;
//                    for(double t=0.0; t<=2*M_PI; t+=0.1){
//                        xIndex = static_cast<unsigned>(radius*cos(t)) + x;
//                        yIndex = static_cast<unsigned>(radius*sin(t)) + y;
//                        double z = colorMap->data()->cell(xIndex, yIndex) + 0.1;
//                        qDebug() << "z = " << z;
//                        z = qMax(z, 0.0);
//                        colorMap->data()->setCell(xIndex, yIndex, z);
//                    }
                }
            }
        }
    }


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
