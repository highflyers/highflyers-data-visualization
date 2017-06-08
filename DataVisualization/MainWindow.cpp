#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QtGlobal>
#include <QFileDialog>

#include <QPair>
#include <QtPositioning/QGeoCoordinate>

#include <MapImageManipulation/PathOverlay.h>

#include <WebSocket/WebSocketServer.h>
#include <WebSocket/ServerStats.h>
#include <GUI/ServerStatus.h>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString mapFilename = QFileDialog::getOpenFileName(this, tr("Open map file"),
                                                       "/home",
                                                       tr(""));

    /// @todo Add config file
    mapProvider = new FileMapProvider(mapFilename, mapFilename);
    /// @todo Set coordinates
    QGeoCoordinate first = QGeoCoordinate();
    first.setLatitude(-1);
    first.setLongitude(-1);
    QGeoCoordinate second = QGeoCoordinate(3, 3,0);
    second.setLongitude(3);
    second.setLatitude(3);
    QPair<QGeoCoordinate, QGeoCoordinate> coordPair(first, second);
    mapFragment = mapProvider->getImage(coordPair);

    qDebug() << mapFragment->limits().first.toString();

    QString logDirName = QFileDialog::getExistingDirectory(this, tr("Select log directory"));
    inputLogger = new DataStorage::InputLogger(logDirName);

    missionControl = new MissionControl::MissionControl(mapFragment, this);

    mapImage = missionControl->getDisplayImage();

    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
    timer->start(TIMER_RATE);

    quint16 port = 1234;
    webSocketServer = new WebSocket::WebSocketServer(port);
    webSocketServer->setLogger(inputLogger);

    connect(webSocketServer, SIGNAL(newWebMessage(Message)), this, SLOT(newMessage(Message)));
    connect(webSocketServer, SIGNAL(newWebMessage(Message)), missionControl, SLOT(newMessage(Message)));
    connect(webSocketServer, SIGNAL(newWebMessage(Message)), this->ui->widget_vehicles, SLOT(newMessage(Message)));
    connect(webSocketServer, SIGNAL(statusUpdate(WebSocket::ServerStats)), this->ui->widget_server, SLOT(updateStatus(WebSocket::ServerStats)));
    webSocketServer->emitUpdate();
    connect(this->ui->output, SIGNAL(pointSelected(QGeoCoordinate)), this->ui->widget_coord, SLOT(update(QGeoCoordinate)));
}

MainWindow::~MainWindow()
{
    delete ui;
    if (webSocketServer) delete webSocketServer;
    if (mapProvider) delete mapProvider;
    if (mapFragment) delete mapFragment;
    if (webSocketServer) delete webSocketServer;
    if (missionControl) delete missionControl;
    if (inputLogger) delete inputLogger;
}

WebSocket::WebSocketServer *MainWindow::getServer()
{
    return this->webSocketServer;
}

void MainWindow::timerTimeout()
{
    //missionControl->mapModel->rewriteImage();
    mapImage->rewriteImage();
    this->ui->output->updateImage(mapImage);
}

void MainWindow::updateImage(DisplayImage *image)
{
    this->mapImage = image;
}
