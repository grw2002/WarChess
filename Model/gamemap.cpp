#include "gamemap.h"
#include <cstdlib>

GameMap::GameMap(QGraphicsScene *scene, QObject *parent) : QObject(parent)
{
    for(int i=1;i<=NUMX;i++) {
        for(int j=1;j<=NUMY;j++) {
            if(rand()&1) {
                m_pBlocks[i][j]=new Dirt();
            } else {
                m_pBlocks[i][j]=new Lava();
            }
            m_pBlocks[i][j]->setLogicPos(QPoint(i,j));
            scene->addItem(m_pBlocks[i][j]);
        }
    }
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget) {
//    Q_UNUSED(option);
//    Q_UNUSED(widget);
//    painter->drawRect(-HALF_BLOCK_SIZE,-HALF_BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE);
    image()->paint(painter,option,widget);
}

void Block::onframeChange(int frameCount) {
    Q_UNUSED(frameCount);
    update();
}

// Dirt

Image* Dirt::m_image=nullptr;

Dirt::Dirt(QGraphicsItem *parent):
    Block(parent)
{
    connect(Dirt::m_image, SIGNAL(frameChanged(int)), this, SLOT(onFrameChange(int)));
}

Dirt::~Dirt(){}

Block::BlockType Dirt::blockType() const {
    return Block::Dirt;
}

const Image* Dirt::image() const {
    return Dirt::m_image;
}


// Lava

Image* Lava::m_image=nullptr;

Lava::Lava(QGraphicsItem *parent):
    Block(parent)
{
    connect(Lava::m_image, SIGNAL(frameChanged(int)), this, SLOT(onFrameChange(int)));
}

Block::BlockType Lava::blockType() const{
    return Block::Lava;
}

Lava::~Lava(){}

const Image* Lava::image() const {
    return Lava::m_image;
}
