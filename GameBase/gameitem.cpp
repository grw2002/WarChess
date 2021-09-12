#include "gameitem.h"
#include "gamecontroller.h"
#include "gamemain.h"
#include "gameui.h"
#include "image.h"


#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>


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
    case GameUI::Icon:
      ((GameIcon *)(m_game->m_pOverlayUI))->onClick(event);
      break;
    default:
      break;
    }
    return;
  }
  if (event->button() == Qt::RightButton) {
    if (m_game->status() == GameMain::Self && !m_game->actioning()) {
      if (QMessageBox::question(nullptr, "提示", "结束当前回合吗") ==
          QMessageBox::Yes) {
        GameController::nextRound(m_game, GameMain::Enemy);
      }
    }
  }
}

void GameItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  m_bClickValid = true;
  QGraphicsItem::mousePressEvent(event);
}

void GameItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  m_bClickValid = false;
  QGraphicsItem::mouseMoveEvent(event);
}

void GameItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  onClick(event);
  QGraphicsItem::mouseReleaseEvent(event);
}
