#ifndef SERVERSTATS_H
#define SERVERSTATS_H

#include <QHostAddress>

namespace WebSocket {

class ServerStats
{
public:
    ServerStats(QHostAddress address, int port, bool active, unsigned numberOfClients);

    bool active;
    QHostAddress address;
    int port;
    unsigned numberOfClients;
};

}

#endif // SERVERSTATS_H
