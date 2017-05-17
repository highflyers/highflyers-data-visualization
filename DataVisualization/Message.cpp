#include "Message.h"

Message::Message(QObject *parent) : QObject(parent)
{
    std::vector<int> temp(MESSAGE_DATA_SIZE, 0);
    data = temp;
}

QString Message::toString()
{
    /// @todo Implement!
    return "Message";
}
