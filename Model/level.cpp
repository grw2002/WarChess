#include "level.h"

Level::Level(QGraphicsScene *scene, QObject *parent) : QObject(parent)
{
    m_pMap=new GameMap(scene,this);
}
