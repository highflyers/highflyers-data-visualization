#ifndef TIMESTATUS_H
#define TIMESTATUS_H

#include <QWidget>
#include <QLCDNumber>
#include <QTime>
#include <QTimer>

namespace Ui {
class TimeStatus;
}

class TimeStatus : public QWidget
{
    Q_OBJECT

public:
    explicit TimeStatus(QWidget *parent = 0);
    ~TimeStatus();

private:
    Ui::TimeStatus *ui;
    QTimer timer;
    QTime time;

private slots:
    void update();
    void display();
    void on_pushButton_reset_clicked();
};

#endif // TIMESTATUS_H
