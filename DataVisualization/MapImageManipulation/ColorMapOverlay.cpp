#include "ColorMapOverlay.h"
#include <QDebug>

ColorMapOverlay::ColorMapOverlay(DisplayImage *parentImage, BeaconColor beaconColor) : MapOverlay(parentImage), beaconColor(beaconColor)
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

    reset();

    colorMapMax = 1.0;
    colorMapMin = 0.0;
    customPlot->rescaleAxes();
    customPlot->setBackground(QColor(255,255,255,0));
}

ColorMapOverlay::~ColorMapOverlay()
{
    delete customPlot;
    delete colorMap;
    delete colorScale;
    delete marginGroup;
    delete parentImage;
}

QImage ColorMapOverlay::toImage()
{
    QPixmap mapPixmap = customPlot->toPixmap(getWidth(), getHeight());
    return mapPixmap.toImage();
}

void ColorMapOverlay::reset()
{
    for (unsigned xIndex = 0; xIndex < parentImage->getWidth(); xIndex += 1)
    {
        for (unsigned yIndex = 0; yIndex < parentImage->getHeight(); yIndex += 1)
        {
            colorMap->data()->setCell(xIndex, yIndex, 1);
        }
    }
}

void ColorMapOverlay::processData(const Message &message)
{
    qDebug();
    /// @todo Implement operations
    parentImage->processData(message);

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
                    for (unsigned xIndex = 0; xIndex < getWidth(); xIndex += 1)
                    {
                        for (unsigned yIndex = 0; yIndex < getHeight(); yIndex += 1)
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

}

QImage ColorMapOverlay::rewriteImage()
{
    colorMap->setDataRange(QCPRange(colorMapMin, colorMapMax));
    return MapOverlay::rewriteImage();
}
