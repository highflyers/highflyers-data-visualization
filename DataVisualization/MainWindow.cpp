#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QtGlobal>
#include <QFileDialog>

#include <QPair>
#include <QtPositioning/QGeoCoordinate>

#include <MapImageManipulation/PathOverlay.h>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString mapFilename = QFileDialog::getOpenFileName(this, tr("Open map file"),
                                                       "/home",
                                                       tr("Images (*.png *.xpm *.jpg)"));
    /// @todo Add config file
    mapProvider = new FileMapProvider(mapFilename, "");
    /// @todo Set coordinates
    QGeoCoordinate first = QGeoCoordinate(1,1,0);
    QGeoCoordinate second = QGeoCoordinate(2,2,0);
    QPair<QGeoCoordinate, QGeoCoordinate> coordPair(first, second);
    mapFragment = mapProvider->getImage(coordPair);

    qDebug() << mapFragment->limits().first.toString();

    mapImage = mapFragment;

    missionControl = new MissionControl::MissionControl(mapFragment, this);

    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
    timer->start(TIMER_RATE);

    bool debug = true;//parser.isSet(dbgOption);
    quint16 port = 1;
    webSocketServer = new WebSocketServer(debug, port);

    connect(webSocketServer, SIGNAL(newWebMessage(Message)), this, SLOT(newMessage(Message)));
    connect(webSocketServer, SIGNAL(newWebMessage(Message)), missionControl, SLOT(newMessage(Message)));
    connect(webSocketServer, SIGNAL(newWebMessage(Message)), this->ui->widget_vehicles, SLOT(newMessage(Message)));
    connect(this->ui->output, SIGNAL(pointSelected(QGeoCoordinate)), this->ui->widget_coord, SLOT(update(QGeoCoordinate)));
    connect(missionControl, SIGNAL(newImage(DisplayImage*)), this, SLOT(updateImage(DisplayImage*)));
}

MainWindow::~MainWindow()
{
    delete webSocketServer;
    delete mapProvider;
    delete mapFragment;
    delete mapImage;
    delete ui;
}

WebSocketServer *MainWindow::getServer()
{
    return this->webSocketServer;
}

void MainWindow::timerTimeout()
{
    qDebug();
    this->ui->output->updateImage(mapImage);
}

void MainWindow::newMessage(const Message &message)
{
//    this->ui->label_message->setText(message.toString());
}

void MainWindow::updateImage(DisplayImage *image)
{
    this->mapImage = image;
}
