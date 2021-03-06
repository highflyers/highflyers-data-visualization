#include "DotOverlay.h"
#include <QDebug>

DotOverlay::DotOverlay(DisplayImage *parentImage, BeaconColor beaconColor, unsigned index) : MapOverlay(parentImage), beaconColor(beaconColor), index(index)
{
    customPlot = new QCustomPlot();
    customPlot->axisRect()->setAutoMargins(QCP::msNone);
    customPlot->axisRect()->setMargins(QMargins(0,0,0,0));

    colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
    colorMap->data()->setSize(parentImage->getWidth(), parentImage->getHeight());
    colorMap->data()->setRange(QCPRange(0, 8), QCPRange(0, 8));

    image = parentImage->rewriteImage();

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

    reset();

    colorMapMax = 1.0;
    colorMapMin = 0.0;
    customPlot->rescaleAxes();
    customPlot->setBackground(QColor(255,255,255,0));
}

DotOverlay::~DotOverlay()
{
    delete customPlot;
    delete colorMap;
    delete colorScale;
    delete marginGroup;
    delete parentImage;
}

QImage DotOverlay::toImage()
{
    QPixmap mapPixmap;
    if(!isFiltered){
        mapPixmap = customPlot->toPixmap(getWidth(), getHeight());
        return mapPixmap.toImage();
    } else {
        QImage resultImage = QImage(getWidth(), getHeight(), QImage::Format_ARGB32_Premultiplied);
        resultImage.fill(qRgba(0, 0, 0, 0));
        return resultImage;
    }
}

void DotOverlay::reset()
{
    for (unsigned xIndex = 0; xIndex < parentImage->getWidth(); xIndex += 1)
    {
        for (unsigned yIndex = 0; yIndex < parentImage->getHeight(); yIndex += 1)
        {
            colorMap->data()->setCell(xIndex, yIndex, 1.0);
        }
    }
    DisplayImage::reset();
}

void DotOverlay::setSensitivity(double value)
{
    this->sensitivity = value;
    calculateWithSensitivityAllCells();
    MapOverlay::setSensitivity(value);
}

void DotOverlay::filter(QVector<bool> filter)
{
    isFiltered = filter.at(index);
    qDebug() << "Overlay number:" << index << " set active to: " << isFiltered;
    parentImage->filter(filter);
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

double DotOverlay::calculateWithSensitivity(double power)
{
    if(power > 1)
    {
        power -= SENSITIVITY_OFFSET;
    }
    if(power > sensitivity && power <= 1)
    {
        power += SENSITIVITY_OFFSET;
    }
    return power;
}

void DotOverlay::calculateWithSensitivityAllCells()
{
    for (unsigned xIndex = 0; xIndex < parentImage->getWidth(); xIndex += 1)
    {
        for (unsigned yIndex = 0; yIndex < parentImage->getHeight(); yIndex += 1)
        {
            double cellValue = colorMap->data()->cell(xIndex, yIndex);
            colorMap->data()->setCell(xIndex, yIndex, calculateWithSensitivity(cellValue));
        }
    }
}

void DotOverlay::processData(const Message &message)
{
    qDebug();
    parentImage->processData(message);

    int x=0;
    int y=0;

    if((x = absoluteLongitudeToRelative(message.position)) != -1){
        qDebug() << "x: " << x;
        if((y = absoluteLatitudeToRelative(message.position)) != -1){
            qDebug() << "y: " << y;

            auto it = message.data.begin();
            it += index;
//            switch(beaconColor){
//                case green:
//                    it+=0;
//                    break;
//                case red:
//                    it+=1;
//                    break;
//                case yellow:
//                    it+=2;
//                    break;
//                case black:
//                    it+=4;
//                    break;
//            }
            auto end_it = it+1;
            for(it; it!=end_it; ++it){
                int rssi = *it;
                double power = rssiNorm(rssi);
                if(power>0){
                    int radius = 0.02 * qMin(getWidth(), getHeight()) * (1-power);
                    qDebug() << "power" << power;
                    for(int ix = qMax(0, x - radius); ix < qMin((int)getWidth(), x + radius); ++ix)
                    {
                        for(int iy = qMax(0, y - radius); iy < qMin((int)getHeight(), y + radius); ++iy)
                        {
                            if(distance(x,y,ix,iy) < radius)
                            {
                                colorMap->data()->setCell(ix, iy, qMin(colorMap->data()->cell(ix, iy), calculateWithSensitivity(power)));
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
    QPixmap mapPixmap;
    if(!isFiltered){
        colorMap->setDataRange(QCPRange(colorMapMin, colorMapMax));
        return MapOverlay::rewriteImage();
    }
    else
    {
        return parentImage->rewriteImage();
    }
}
