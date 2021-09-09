#include "gameitem.h"
#include "gamemain.h"
#include "gameui.h"
#include "image.h"
#include <QGraphicsItem>


GameItem::GameItem(QGraphicsItem *parent)
    : QGraphicsItem(parent), m_logicPos(-1, -1) {}

GameItem::~GameItem() {}

void GameItem::setLogicPos(QPoint logicPos) {
  setPos(QPointF(HALF_BLOCK_SIZE + (logicPos.x() - 1) * BLOCK_SIZE,
                 HALF_BLOCK_SIZE + (logicPos.y() - 1) * BLOCK_SIZE));
  m_logicPos = logicPos;
}

QPoint GameItem::LogicPos() const { return m_logicPos; }

void GameItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
  image()->paint(painter, option, widget);
}

QRectF GameItem::boundingRect() const { return image()->boundingRect(); }

void GameItem::onFrameChange(int frameNumber) {
  Q_UNUSED(frameNumber);
  update();
}

void GameItem::onClick(QGraphicsSceneMouseEvent *event) {
  qDebug() << "base onclick" << event->pos();
  event->setPos(event->scenePos());
  if (m_game->m_pOverlayUI) {
    switch (m_game->m_pOverlayUI->uiType()) {
    case GameUI::UnitMove:
      ((UnitMove *)(m_game->m_pOverlayUI))->onClick(event);
      break;
    case GameUI::UnitActionMenu:
      ((UnitActionMenu *)(m_game->m_pOverlayUI))->onClick(event);
      break;
    case GameUI::UnitAttack:
      ((UnitAttack *)(m_game->m_pOverlayUI))->onClick(event);
      break;
    default:
      break;
    }
  }
  Q_UNUSED(event);
}
