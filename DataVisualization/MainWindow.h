#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>
#include <QTimer>
#include <QPixmap>
#include <QSharedPointer>

#include <MapImageManipulation/FileMapProvider.h>
#include <MapImageManipulation/MapFragment.h>
#include <MapImageManipulation/ColorMapOverlay.h>
#include <WebSocketServer/WebSocketServer.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    WebSocketServer* getServer();

private:
    const unsigned TIMER_RATE = 1000;
    Ui::MainWindow *ui;
    QTimer *timer;
    MapProvider *mapProvider;
    DisplayImage *mapFragment;
    DisplayImage *mapImage;
    WebSocketServer *webSocketServer;

private slots:
    void timerTimeout();
};

#endif // MAINWINDOW_H
