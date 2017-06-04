#include "ServerStatus.h"
#include "ui_ServerStatus.h"

#include <QDebug>

ServerStatus::ServerStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerStatus)
{
    ui->setupUi(this);
}

ServerStatus::~ServerStatus()
{
    delete ui;
}

void ServerStatus::updateStatus(const WebSocket::ServerStats &status)
{
    qDebug();
    this->ui->lineEdit_IP->setText(status.address.toString());
    this->ui->lineEdit_port->setText(QString::number(status.port));
    this->ui->label_clients->setText(QString::number(status.numberOfClients));
    if(status.active)
    {
        this->ui->label_status->setText(tr("Active"));
    }
    else
    {
        this->ui->label_status->setText(tr("Inactive"));
    }
}
