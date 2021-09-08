#include "image.h"

#include "GameConfig.h"

Image::Image(const QString& path, int width, int height, bool isGif, QPoint anchor, bool horizonMirrored,QObject *parent):
    QObject(parent),
    m_anchor(anchor),
    m_width(width),
    m_height(height),
    m_bounding(QRectF(-anchor.x(), -anchor.y(), m_width, m_height)),
    m_bGif(isGif),
    m_horizonMirrored(horizonMirrored)
{
    if(m_bGif) {
        m_movie=new QMovie(path);
        m_movie->start();
        connect(m_movie,SIGNAL(frameChanged(int)),this,SIGNAL(frameChanged(int)));
    } else {
        if(m_horizonMirrored) {
            m_image=new QImage(QImage(path).mirrored(true,false));
        } else {
            m_image=new QImage(path);
        }
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
                  QWidget *widget, bool horizonMirrored) const
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(m_bGif) {
        painter->drawImage(m_bounding, m_movie->currentImage().mirrored(horizonMirrored,false));
    } else {
        painter->drawImage(m_bounding, m_image->mirrored(horizonMirrored,false));
    }
}
