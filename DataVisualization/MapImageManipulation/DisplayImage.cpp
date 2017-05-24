#include "DisplayImage.h"

DisplayImage::DisplayImage(QObject *parent) : QObject(parent)
{

}

double DisplayImage::getWidth()
{
    return image.width();
}

double DisplayImage::getHeight()
{
    return image.height();
}
