#include "InputLogger.h"

#include <QDebug>
#include <QDateTime>
#include <QDir>

namespace DataStorage {

InputLogger::InputLogger(const QString &dirName)
{
    qDebug() << dirName;
    QString filename = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".log";
    init(dirName, filename);
}

InputLogger::InputLogger(const QString &dirName, const QString &filename)
{
    qDebug();
    init(dirName, filename);
}

InputLogger::~InputLogger()
{
    delete stream;
    delete file;
}

void InputLogger::newData(QString data)
{
    qDebug();
    data.replace("\r", " ");
    data.replace("\n", " ");
    (*stream) << QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") << "\t" << data << "\n";
    stream->flush();
}

void InputLogger::init(const QString &dirName, const QString &filename)
{
    QString fullFilename = dirName + QDir::separator() + filename;
    qDebug() << dirName << filename << fullFilename;
    file = new QFile(fullFilename);
    file->open(QIODevice::WriteOnly | QIODevice::Append);
    stream = new QTextStream(file);
}

}
