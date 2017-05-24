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
    QGeoCoordinate coord;
    QPair<QGeoCoordinate, QGeoCoordinate> coordPair(coord, coord);
    mapFragment = mapProvider->getImage(coordPair);

    mapImage = new PathOverlay(new ColorMapOverlay(mapFragment));

    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
    timer->start(1000);

    bool debug = true;//parser.isSet(dbgOption);
    quint16 port = 1;
    webSocketServer = new WebSocketServer(debug, port);

    connect(webSocketServer, SIGNAL(newWebMessage(Message)), mapImage, SLOT(processData(Message)));
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
    qDebug() << "Updating image";

    Message message;
    mapImage->processData(message);
    this->ui->output->updateImage(mapImage->image);
}
