#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QList>
#include <QByteArray>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
#include <Message.h>
#include <QJsonObject>

class WebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketServer(quint16 port, bool debug = false, QObject *parent = Q_NULLPTR);
    ~WebSocketServer();

signals:
    void closed();
    void newWebMessage(const Message &msg);

private slots:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug;

    QJsonObject objectFromString(const QString &m);
};

#endif // WEBSOCKETSERVER_H
