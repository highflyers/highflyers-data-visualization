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

    colorMapOverlay = new ColorMapOverlay(mapFragment->image.width(), mapFragment->image.height(), this);
    pathOverlay = new PathOverlay(mapFragment->image.width(), mapFragment->image.height(), this);

    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
    timer->start(1000);

    bool debug = true;//parser.isSet(dbgOption);
    quint16 port = 1;
    webSocketServer = new WebSocketServer(debug, port);

    connect(webSocketServer, SIGNAL(newWebMessage(Message)), colorMapOverlay, SLOT(processData(Message)));
}

MainWindow::~MainWindow()
{
    delete webSocketServer;
    delete colorMapOverlay;
    delete pathOverlay;
    delete ui;
}

WebSocketServer *MainWindow::getServer()
{
    return this->webSocketServer;
}

void MainWindow::timerTimeout()
{
    qDebug() << "Updating image";
    if(mapFragment)
    {
        this->ui->output->setMap(mapFragment->image);
    }

    Message message;
    colorMapOverlay->processData(message);
    pathOverlay->processData(message);
    this->ui->output->updateOverlay(colorMapOverlay->toImage());
    this->ui->output->updatePath(pathOverlay->toImage());
}
