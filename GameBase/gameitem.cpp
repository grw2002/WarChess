#include "gameitem.h"
#include <QGraphicsItem>

GameItem::GameItem(QGraphicsItem *parent):
    QGraphicsItem(parent)
{}

GameItem::~GameItem(){}

void GameItem::setLogicPos(QPoint logicPos) {
    setPos(QPointF( HALF_BLOCK_SIZE+(logicPos.x()-1)*BLOCK_SIZE,
                    HALF_BLOCK_SIZE+(logicPos.y()-1)*BLOCK_SIZE));
    m_logicPos=logicPos;
}

QPoint GameItem::LogicPos() const {
    return m_logicPos;
}

void GameItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
    image()->paint(painter, option, widget);
}

QRectF GameItem::boundingRect() const {
    return image()->boundingRect();
}

void GameItem::onFrameChange(int frameNumber) {
    Q_UNUSED(frameNumber);
    update();
}
