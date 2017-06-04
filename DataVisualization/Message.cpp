#include "Message.h"

Message::Message(QObject *parent) : QObject(parent)
{
    data = QVector<int>(MESSAGE_DATA_SIZE, 0);
}

QString Message::toString()
{
    /// @todo Implement!
    return "Message";
}
