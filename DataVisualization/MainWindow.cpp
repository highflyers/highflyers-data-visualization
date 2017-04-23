#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QtGlobal>
#include <QFileDialog>

#include <QPair>
#include <QtPositioning/QGeoCoordinate>

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

    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerTimeout()
{
    if(mapFragment)
    {
        this->ui->output->setMap(mapFragment->image);
    }

    Message message;
    colorMapOverlay->processData(message);
    this->ui->output->updateOverlay(colorMapOverlay->toImage());
}
