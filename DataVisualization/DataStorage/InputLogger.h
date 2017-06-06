#ifndef INPUTLOGGER_H
#define INPUTLOGGER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>

namespace DataStorage
{

class InputLogger : public QObject
{
    Q_OBJECT
public:
    InputLogger(const QString &dirName);
    InputLogger(const QString &dirName, const QString &filename);
    ~InputLogger();

public slots:
    void newData(QString data);

private:
    void init(const QString &dirName, const QString &filename);
    QFile *file = nullptr;
    QTextStream *stream = nullptr;
};

}

#endif // INPUTLOGGER_H
