#include "CoordinateDisplay.h"
#include "ui_CoordinateDisplay.h"

CoordinateDisplay::CoordinateDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoordinateDisplay)
{
    ui->setupUi(this);
}

CoordinateDisplay::~CoordinateDisplay()
{
    delete ui;
}

void CoordinateDisplay::update(const QGeoCoordinate &coordinate)
{
    double deg, min, sec, pos;
    pos = coordinate.latitude();
    deg = (int)pos;
    min = (pos - deg) * 60;
    sec = (min - (int)min) * 60;
    min = (int)min;
    this->ui->label_lat->setText(QString::number(deg) + " " + QString::number(min) + " " + QString::number(sec));
    pos = coordinate.longitude();
    deg = (int)pos;
    min = (pos - deg) * 60;
    sec = (min - (int)min) * 60;
    min = (int)min;
    this->ui->label_lon->setText(QString::number(deg) + " " + QString::number(min) + " " + QString::number(sec));
}
