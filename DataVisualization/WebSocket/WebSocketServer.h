#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QList>
#include <QByteArray>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
#include <Message.h>
#include <QJsonObject>

#include <WebSocket/ServerStats.h>
#include <DataStorage/InputLogger.h>

namespace WebSocket {

class WebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketServer(quint16 port, QObject *parent = Q_NULLPTR);
    ~WebSocketServer();
    void emitUpdate();
    void setLogger(DataStorage::InputLogger *logger);

signals:
    void closed();
    void newWebMessage(const Message &msg);
    void statusUpdate(WebSocket::ServerStats status);

private slots:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;

    QJsonObject objectFromString(const QString &m);
    QHostAddress localAddress();

    DataStorage::InputLogger *inputLogger = nullptr;
};

}

#endif // WEBSOCKETSERVER_H
