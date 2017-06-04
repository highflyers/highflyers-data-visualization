#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qSetMessagePattern("%{time}\t%{type}\t%{function} %{message}");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
