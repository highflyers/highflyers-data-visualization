#include "WebSocketServer.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>

QT_USE_NAMESPACE


WebSocketServer::WebSocketServer(quint16 port, bool debug, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_clients(),
    m_debug(debug)
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug)
            qDebug() << "WebSocketServer listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &WebSocketServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &WebSocketServer::closed);
    }
}


WebSocketServer::~WebSocketServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}


void WebSocketServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &WebSocketServer::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WebSocketServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &WebSocketServer::socketDisconnected);

    m_clients << pSocket;
}


void WebSocketServer::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "Message received:" << message;
    if (pClient) {
        pClient->sendTextMessage(message);
    }
    Message *msg = new Message();
    QJsonObject object = objectFromString(message);
    msg->ID = object["ID"].toInt();
    msg->name = object["name"].toString();

    msg->position.setLatitude(object["latitude"].toDouble());
    msg->position.setLongitude(object["longitude"].toDouble());
    msg->position.setAltitude(object["altitude"].toDouble());

    QJsonArray data = object["data"].toArray();
    auto dataIt = msg->data.begin();
    qDebug() << "Data: ";
    for(auto it = data.begin(); it != data.end(); ++it){
        if(dataIt != msg->data.end()){
            QJsonValue temp = *it;
            *dataIt = temp.toInt();
            qDebug() << *dataIt;
            ++dataIt;
        } else {
            break;
        }
    }

    qDebug() << msg->toString();

    emit newWebMessage(*msg);
    delete msg;
}


void WebSocketServer::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "Binary Message received:" << message;
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}


void WebSocketServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

QJsonObject WebSocketServer::objectFromString(const QString &m)
{
    QJsonObject obj;

    QJsonDocument doc = QJsonDocument::fromJson(m.toUtf8());

      // check validity of the document
      if(!doc.isNull())
      {
          if(doc.isObject())
          {
              obj = doc.object();
          }
          else
          {
              qDebug() << "Document is not an object" << endl;
          }
      }
      else
      {
          qDebug() << "Invalid JSON...\n" << m << endl;
      }

      return obj;
}
