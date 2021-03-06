#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QtPositioning/QGeoCoordinate>

#include <QVector>

/**
 * @brief Representation of a data sent by drone
 */
class Message : public QObject
{
    Q_OBJECT

private:
    const unsigned MESSAGE_DATA_SIZE = 16;

public:
    explicit Message(QObject *parent = 0);

    int ID;
    QString name;
    QGeoCoordinate position;
    QVector<int> data;

    QString toString() const;
};

#endif // MESSAGE_H
