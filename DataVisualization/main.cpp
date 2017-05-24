#include "MainWindow.h"
#include <QApplication>
#include <WebSocketServer/WebSocketServer.h>

int main(int argc, char *argv[])
{
    qSetMessagePattern("%{time}\t%{type}\t%{function} %{message}");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
