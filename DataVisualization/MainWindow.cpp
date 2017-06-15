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
                                                       tr("*.hf"));

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
    webSocketServer->emitUpdate();
    connect(this->ui->output, SIGNAL(pointSelected(QGeoCoordinate)), this->ui->widget_coord, SLOT(update(QGeoCoordinate)));

    this->ui->horizontalSlider->setValue(100);
    this->ui->widget_becon_select->setNumberOfBeacons(10);
    connect(this->ui->widget_becon_select, SIGNAL(filterApplied(QVector<bool>)), this, SLOT(filterApplied(QVector<bool>)));
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
    bool path = false, marks = false;
    if(this->ui->checkBox_path->checkState() == Qt::Checked) path = true;
    if(this->ui->checkBox_marks->checkState() == Qt::Checked) marks = true;
    mapImage = missionControl->getDisplayImage(path, marks);
    mapImage->rewriteImage();
    this->ui->output->updateImage(mapImage);
}

void MainWindow::updateImage(DisplayImage *image)
{
    this->mapImage = image;
}

void MainWindow::on_pushButton_clicked()
{
    missionControl->reset();
    timerTimeout();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{

}

void MainWindow::on_pushButton_2_clicked()
{
    int value = this->ui->horizontalSlider->value();
    this->ui->label_sensitivity->setText(tr("Czułość") + " (" + QString::number(value) + "%)");
    missionControl->setSensitivity(value / 100.0);
}

void MainWindow::filterApplied(QVector<bool> filter)
{
    qDebug() << filter;
}
