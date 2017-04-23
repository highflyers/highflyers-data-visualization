#ifndef IMAGEMIXER_H
#define IMAGEMIXER_H

#include <QObject>
#include <QPixmap>
#include <QImage>

/**
 * @brief Combines map image with an overlay
 */
class ImageMixer : public QObject
{
    Q_OBJECT
public:
    explicit ImageMixer(QObject *parent = 0);

    void setMap(const QImage &mapImage);

signals:

public slots:
    void updateOverlay(const QImage &overlay);

private:
    QPixmap *mapImagePixmap;
};

#endif // IMAGEMIXER_H
