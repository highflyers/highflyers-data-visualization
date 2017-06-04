#include "CoordinateDisplay.h"
#include "ui_CoordinateDisplay.h"

#include <QString>
#include <QStringList>

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
    QStringList tokens = coordinate.toString().split(',',  QString::SkipEmptyParts);
    this->ui->label_lon->setText(tokens[0].trimmed());
    this->ui->label_lat->setText(tokens[1].trimmed());
}
