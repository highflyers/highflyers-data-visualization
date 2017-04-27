#include "ServerStatus.h"
#include "ui_ServerStatus.h"

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

void ServerStatus::updateStatus(const ServerStatus &status)
{
    /// @todo Implement!
}
