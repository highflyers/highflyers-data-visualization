#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>
#include <QTimer>
#include <QPixmap>
#include <QSharedPointer>
#include <QVector>

#include <MapImageManipulation/FileMapProvider.h>
#include <MapImageManipulation/MapFragment.h>
#include <MapImageManipulation/ColorMapOverlay.h>
#include <WebSocket/WebSocketServer.h>

#include <MissionControl/MissionControl.h>

#include <GUI/VehicleContainer.h>
#include <DataStorage/InputLogger.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    WebSocket::WebSocketServer* getServer();
    void updateImage(DisplayImage *image);

private:
    const unsigned TIMER_RATE = 1000;
    Ui::MainWindow *ui;
    QTimer *timer = nullptr;
    MapProvider *mapProvider = nullptr;
    DisplayImage *mapFragment = nullptr;
    DisplayImage *mapImage = nullptr;
    WebSocket::WebSocketServer *webSocketServer = nullptr;
    MissionControl::MissionControl *missionControl = nullptr;
    DataStorage::InputLogger *inputLogger = nullptr;

private slots:
    void timerTimeout();

    void on_pushButton_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_2_clicked();

    void filterApplied(QVector<bool> filter);
};

#endif // MAINWINDOW_H
