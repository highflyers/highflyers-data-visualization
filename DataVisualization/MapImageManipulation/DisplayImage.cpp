#include "DisplayImage.h"

DisplayImage::DisplayImage(DisplayImage *parentImage) : QObject(parentImage), parentImage(parentImage)
{

}

QPair<QGeoCoordinate, QGeoCoordinate> DisplayImage::limits() const
{
    if(parentImage)
    {
        return parentImage->limits();
    }
    else
    {
        QGeoCoordinate coord;
        return QPair<QGeoCoordinate, QGeoCoordinate>(coord, coord);
    }
}

unsigned DisplayImage::getWidth()
{
    if(parentImage)
    {
        return parentImage->getWidth();
    }
    else
    {
        return 0;
    }
}

unsigned DisplayImage::getHeight()
{
    if(parentImage)
    {
        return parentImage->getHeight();
    }
    else
    {
        return 0;
    }
}

void DisplayImage::reset()
{
    if(parentImage)
    {
        parentImage->reset();
    }
}
