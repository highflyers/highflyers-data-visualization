#ifndef COORDINATEDISPLAY_H
#define COORDINATEDISPLAY_H

#include <QWidget>
#include <QGeoCoordinate>

namespace Ui {
class CoordinateDisplay;
}

class CoordinateDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit CoordinateDisplay(QWidget *parent = 0);
    ~CoordinateDisplay();

private:
    Ui::CoordinateDisplay *ui;

public slots:
    void update(const QGeoCoordinate &coordinate);
};

#endif // COORDINATEDISPLAY_H
