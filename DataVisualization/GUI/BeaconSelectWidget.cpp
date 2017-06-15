#include "BeaconSelectWidget.h"
#include "ui_BeaconSelectWidget.h"

#include <QCheckBox>

BeaconSelectWidget::BeaconSelectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BeaconSelectWidget)
{
    ui->setupUi(this);
}

BeaconSelectWidget::~BeaconSelectWidget()
{
    delete ui;
}

void BeaconSelectWidget::setNumberOfBeacons(int n)
{
    for(int i = 0; i < n; ++i)
    {
        QWidget *checbox = new QCheckBox(QString::number(i+1), this);
        this->ui->horizontalLayout_boxes->addWidget(checbox);
        checkboxes.append(checbox);
    }
}

void BeaconSelectWidget::clear()
{
    foreach (QWidget *widget, checkboxes) {
        delete widget;
    }
    checkboxes.clear();
}

void BeaconSelectWidget::on_pushButton_clicked()
{
    QVector<bool> filter;
    foreach (QWidget *widget, checkboxes) {
        QCheckBox *checkbox = static_cast<QCheckBox*>(widget);
        bool checkboxChecked = false;
        if(checkbox->checkState() == Qt::Checked) checkboxChecked = true;
        filter.append(checkboxChecked);
    }
    emit filterApplied(filter);
}
