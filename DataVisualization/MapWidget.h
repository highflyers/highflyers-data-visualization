#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QResizeEvent>
#include <QLabel>
#include <QPixmap>
#include <QImage>

/**
 * @brief A widget responsible for displaying a map (as QImage).
 */
class MapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget *parent = 0);

    int height() const;
    int width() const;

    void setPixmap(const QPixmap &pixmap);

    void resizeEvent(QResizeEvent *event);

signals:

public slots:
    void updateImage(const QImage &displayImage);

private:
    QLabel *label;
    int h, w;
    QPixmap *mapImagePixmap = nullptr;
    QImage displayImage;
    void redrawContents();
};

#endif // MAPWIDGET_H
