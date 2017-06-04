#include "ServerStats.h"

namespace WebSocket {

ServerStats::ServerStats(QHostAddress address, int port, bool active, unsigned numberOfClients):
    address(address), port(port), active(active), numberOfClients(numberOfClients)
{
}

}
