#include "gamemap.h"
#include "unit.h"
#include "level.h"
#include "gamescene.h"

Level::Level(GameScene *scene, QObject *parent) : QObject(parent)
{
    m_pMap=new GameMap(scene,this);
}

Level::~Level() {
    delete m_pMap;
}
