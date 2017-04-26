#include "ColorMapOverlay.h"

ColorMapOverlay::ColorMapOverlay(QObject *parent) : ColorMapOverlay(1, 1, parent)
{
}

ColorMapOverlay::ColorMapOverlay(unsigned width, unsigned height, QObject *parent) : MapOverlay(parent), width(width), height(height)
{
    customPlot = new QCustomPlot();
    customPlot->axisRect()->setAutoMargins(QCP::msNone);
    customPlot->axisRect()->setMargins(QMargins(0,0,0,0));

    colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
    colorMap->data()->setSize(width, height);
    colorMap->data()->setRange(QCPRange(0, 8), QCPRange(0, 8));

    colorScale = new QCPColorScale(customPlot);
    colorMap->setColorScale(colorScale);
    QCPColorGradient gradient(QCPColorGradient::gpThermal);
    colorMap->setGradient(gradient.inverted());

    customPlot->rescaleAxes();
}

ColorMapOverlay::~ColorMapOverlay()
{
    delete customPlot;
}

QImage ColorMapOverlay::toImage()
{
    QPixmap mapPixmap = customPlot->toPixmap(width, height);
    return mapPixmap.toImage();
}

void ColorMapOverlay::processData(const Message &message)
{
    /// @todo Implement operations
    double x, y, z;
    for (unsigned xIndex = 0; xIndex < width; xIndex += 1)
    {
        for (unsigned yIndex = 0; yIndex < height; yIndex += 1)
        {
            colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
            z = qSin(x)*qCos(y);
            z += 0.2;
            z = qMax(z, 0.0);
            colorMap->data()->setCell(xIndex, yIndex, z);
        }
    }
    colorMap->rescaleDataRange();
}
