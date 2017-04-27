#include "TimeStatus.h"
#include "ui_TimeStatus.h"

TimeStatus::TimeStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeStatus)
{
    ui->setupUi(this);

    timer.setSingleShot(false);
    timer.setInterval(1000);
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start();

    time = this->ui->timeEdit->time();
    display();
}

TimeStatus::~TimeStatus()
{
    delete ui;
}

void TimeStatus::update()
{
    if(this->ui->pushButton_start_stop->isChecked())
    {
        if(time > QTime(0, 0, 0, 0))
            time = time.addSecs(-1);
        display();
    }
}

void TimeStatus::display()
{
    QString displayString = time.toString("hh:mm:ss");
    if(time.second() % 2 != 0)
    {
        displayString[2] = ' ';
        displayString[5] = ' ';
    }
    this->ui->lcdNumber->display(displayString);
}

void TimeStatus::on_pushButton_reset_clicked()
{
    time = this->ui->timeEdit->time();
    this->ui->pushButton_start_stop->setChecked(false);
    display();
}
