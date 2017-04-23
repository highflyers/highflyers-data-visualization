#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

/**
 * @brief Representation of a data sent by drone
 */
class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = 0);

signals:

public slots:
};

#endif // MESSAGE_H
