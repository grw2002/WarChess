#include "gamescene.h"
#include "gameitem.h"
#include "gamemain.h"

#include <QDebug>

GameScene::GameScene(GameMain *game, QObject *parent):
    QGraphicsScene(parent),
    m_game(game)
{

}

GameScene::~GameScene(){}

void GameScene::addItem(GameItem *item) {
    QGraphicsScene::addItem(item);
    item->m_game=m_game;
}
