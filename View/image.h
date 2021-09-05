#ifndef IMAGE_H
#define IMAGE_H

//#include "gameitem.h"

#include <QObject>
#include <QPainter>
#include <QImage>
#include <QMovie>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

class Image : public QObject
{
    Q_OBJECT
public:
    Image(const QString& path, int width, int height, bool isGif = false, QPoint anchor=QPoint(0,0), QObject *parent = nullptr);
    virtual ~Image();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) const;

protected slots:
//    void timerEvent(QTimerEvent *event) override {
//        parent()->event(event);
//    }

private:
    QImage *m_image;
    QMovie *m_movie;
    const QPoint m_anchor;
    const int m_width, m_height;
    const QRectF m_bounding;
    const bool m_bGif;

signals:
    void frameChanged(int);
};

#endif // IMAGE_H
