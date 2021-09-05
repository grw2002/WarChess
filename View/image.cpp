#include "image.h"

#include "GameConfig.h"

Image::Image(const QString& path, int width, int height, bool isGif, QPoint anchor, QObject *parent):
    QObject(parent),
    m_anchor(anchor),
    m_width(width),
    m_height(height),
    m_bounding(QRectF(-anchor.x(), -anchor.y(), m_width, m_height)),
    m_bGif(isGif)
{
    if(m_bGif) {
        m_movie=new QMovie(path);
        m_movie->start();
        connect(m_movie,SIGNAL(frameChanged(int)),this,SIGNAL(frameChanged(int)));
//        connect(m_movie,SIGNAL(frameChanged(int)),parent,SLOT(onFrameChange(int)));
//        startTimer(1000 / FPS);
    } else {
        m_image=new QImage(path);
    }
}

Image::~Image() {
    if(m_bGif) {
        delete m_movie;
    } else {
        delete m_image;
    }
}

QRectF Image::boundingRect() const
{
    return m_bounding;
}

void Image::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) const
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(m_bGif) {
        painter->drawImage(m_bounding, m_movie->currentImage());
    } else {
        painter->drawImage(m_bounding, *m_image);
    }
}
