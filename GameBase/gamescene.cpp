#include "gamescene.h"
#include "gameitem.h"
#include "gamemain.h"

#include <QEvent>
#include <QGraphicsSceneMouseEvent>


GameScene::GameScene(GameMain *game, QObject *parent)
    : QGraphicsScene(parent), m_game(game) {
  setItemIndexMethod(QGraphicsScene::NoIndex);
}

GameScene::~GameScene() {}

void GameScene::addItem(GameItem *item) {
  QGraphicsScene::addItem(item);
  item->m_game = m_game;
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  m_pressPos = mouseEvent->screenPos();
}

void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (m_pressPos == mouseEvent->screenPos()) {
    QGraphicsScene::mousePressEvent(mouseEvent);
  }
}
