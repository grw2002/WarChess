#ifndef GAMEITEM_H
#define GAMEITEM_H

#include "GameConfig.h"
#include "image.h"

#include <QGraphicsItem>
#include <QObject>

class GameItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    GameItem(QGraphicsItem *parent = nullptr);

    virtual ~GameItem();

    void setLogicPos(QPoint);

    QPoint LogicPos() const;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    virtual QRectF boundingRect() const override;

    virtual const Image* image() const = 0;


protected slots:
    void onFrameChange(int frameNumber);

private:
    QPoint m_logicPos;
};

#endif // GAMEITEM_H
