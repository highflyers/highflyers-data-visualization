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

    mapImage = new PathOverlay(new ColorMapOverlay(new ColorMapOverlay(new ColorMapOverlay(new ColorMapOverlay(mapFragment, green), yellow),red), black));

    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
    timer->start(TIMER_RATE);

    bool debug = true;//parser.isSet(dbgOption);
    quint16 port = 1;
    webSocketServer = new WebSocketServer(debug, port);

    connect(webSocketServer, SIGNAL(newWebMessage(Message)), mapImage, SLOT(processData(Message)));
    connect(this->ui->output, SIGNAL(pointSelected(QGeoCoordinate)), this->ui->widget_coord, SLOT(update(QGeoCoordinate)));
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
    static unsigned i=0;
    qDebug() << mapImage->limits().first.toString();
    Message message;
    message.position.setLongitude(1+(i*0.01));
    message.position.setLatitude(1+(i*0.01));
    static const int arr[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<int> vec (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    ++i;
//    unsigned base = 52;
//    if(i == base)
//        vec.at(0) = 250;

//    if(i == base+5)
//        vec.at(0) = 200;

//    if(i == base+10)
//        vec.at(0) = 180;

//    if(i == base+15)
//        vec.at(0) = 200;

//    if(i == base+20)
//        vec.at(0) = 250;

    //wiem że prowizora, ale tak najlatwiej to bylo testowac
    unsigned base = 15;
    if(i == base)
        vec.at(0) = 50;

    if(i == base + 1)
        vec.at(0) = 47;

    if(i == base + 2)
        vec.at(0) = 45;

    if(i == base + 3)
        vec.at(0) = 47;

    if(i == base + 4)
        vec.at(0) = 50;

    if(i == base + 15)
        vec.at(5) = 50;

    if(i == base + 16)
        vec.at(5) = 47;

    if(i == base + 17)
        vec.at(5) = 45;

    if(i == base + 18)
        vec.at(5) = 47;

    if(i == base + 19)
        vec.at(5) = 50;


    if(i == base + 25)
        vec.at(9) = 50;

    if(i == base + 26)
        vec.at(9) = 47;

    if(i == base + 27)
        vec.at(9) = 45;

    if(i == base + 28)
        vec.at(9) = 47;

    if(i == base + 29)
        vec.at(9) = 50;

    if(i == base + 35)
        vec.at(13) = 50;

    if(i == base + 36)
        vec.at(13) = 47;

    if(i == base + 37)
        vec.at(13) = 45;

    if(i == base + 38)
        vec.at(13) = 47;

    if(i == base + 39)
        vec.at(13) = 50;


    message.data = vec;
    qDebug() << "Message in iteration " << i;
    for(auto it = message.data.begin(); it != message.data.end(); ++it)
        qDebug() << *it;

    mapImage->processData(message);
    this->ui->output->updateImage(mapImage);
}
