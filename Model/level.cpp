#include "level.h"
#include "gamemap.h"
#include "gamescene.h"
#include "unit.h"


Level::Level(GameScene *scene, QObject *parent) : QObject(parent) {
  m_pMap = new GameMap(scene, this);
}

Level::~Level() { delete m_pMap; }
