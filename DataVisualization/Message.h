#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QtPositioning/QGeoCoordinate>

/**
 * @brief Representation of a data sent by drone
 */
class Message : public QObject
{
    Q_OBJECT

private:
    static const unsigned MESSAGE_DATA_SIZE = 16;

public:
    explicit Message(QObject *parent = 0);

    int ID;
    QString name;
    QGeoCoordinate position;
    int data[MESSAGE_DATA_SIZE];

    QString toString();
};

#endif // MESSAGE_H
