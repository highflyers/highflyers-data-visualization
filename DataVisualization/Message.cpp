#include "Message.h"
#include <QVector>

Message::Message(QObject *parent) : QObject(parent)
{
    std::vector<int> temp(MESSAGE_DATA_SIZE, 0);
    data = temp;
}

QString Message::toString() const
{
    QString ret;
    ret += name + "\n";
    ret += QString::number(ID) + ", " + name + "\n";
    foreach (int v, QVector<int>::fromStdVector(data)) {
        ret+=QString::number(v) + ", ";
    }
    return ret;
}
