#ifndef SERVERSTATUS_H
#define SERVERSTATUS_H

#include <QWidget>
#include <ServerStatus.h>

#include <WebSocket/ServerStats.h>

namespace Ui {
class ServerStatus;
}

class ServerStatus : public QWidget
{
    Q_OBJECT

public:
    explicit ServerStatus(QWidget *parent = 0);
    ~ServerStatus();

public slots:
    void updateStatus(const WebSocket::ServerStats &status);

private:
    Ui::ServerStatus *ui;
};

#endif // SERVERSTATUS_H
