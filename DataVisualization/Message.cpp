#include "Message.h"
#include <QVector>

Message::Message(QObject *parent) : QObject(parent)
{
    data = QVector<int>(MESSAGE_DATA_SIZE, 0);
}

QString Message::toString() const
{
    QString ret;
    ret += name + "\n";
    ret += position.toString() + "\n";
    ret += QString::number(ID) + ", " + name + "\n";
    foreach (int v, data) {
        ret+=QString::number(v) + ", ";
    }
    return ret;
}
