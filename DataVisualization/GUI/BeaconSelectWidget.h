#ifndef BEACONSELECTWIDGET_H
#define BEACONSELECTWIDGET_H

#include <QWidget>
#include <QList>
#include <QVector>

namespace Ui {
class BeaconSelectWidget;
}

class BeaconSelectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BeaconSelectWidget(QWidget *parent = 0);
    ~BeaconSelectWidget();

    void setNumberOfBeacons(int n);
    void clear();

signals:
    void filterApplied(QVector<bool> filter);

private slots:
    void on_pushButton_clicked();

private:
    Ui::BeaconSelectWidget *ui;
    QList<QWidget *> checkboxes;

};

#endif // BEACONSELECTWIDGET_H
