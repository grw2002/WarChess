#include "gamemap.h"
#include "image.h"
#include <cstdlib>

int map[NUMX+2][NUMY+2]=
//{{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},{3,3,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,3,3},{3,3,6,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,0,0,2,0,0,0,0,0,0,0,0,1,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,2,2,0,2,2,0,0,0,0,0,0,1,1,1,1,1,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,6,6,0,0,1,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,2,2,2,2,2,0,0,6,6,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,2,0,0,0,0,0,0,1,1,1,1,1,0,4,6,3,3},{3,3,6,4,0,2,2,2,2,2,0,0,0,0,0,0,0,0,1,0,0,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,6,3,3},{3,3,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,3,3},{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}}
{{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},{3,3,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,3,3},{3,3,6,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,7,7,7,0,0,0,0,0,0,4,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,7,7,7,0,0,0,0,0,0,4,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,7,7,7,0,0,0,0,0,0,4,4,4,4,4,4,4,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,3,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,3,0,0,3,0,0,0,0,0,4,4,4,4,4,4,4,0,4,6,3,3},{3,3,6,4,0,3,0,0,3,0,0,0,0,0,0,0,0,4,0,0,0,0,4,6,3,3},{3,3,6,4,0,3,3,3,3,0,0,0,0,0,0,0,0,4,0,0,0,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,6,6,4,4,4,4,4,4,4,0,4,6,3,3},{3,3,6,4,0,3,3,3,3,3,3,3,6,6,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,0,0,3,0,3,0,0,0,0,4,4,4,4,4,4,4,0,4,6,3,3},{3,3,6,4,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,4,0,4,6,3,3},{3,3,6,4,0,3,0,0,0,0,0,3,0,0,0,0,0,0,0,0,4,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,0,4,6,3,3},{3,3,6,4,0,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,3,0,0,0,0,0,0,5,5,5,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,3,0,0,0,0,0,0,5,5,5,0,4,6,3,3},{3,3,6,4,0,3,3,3,3,3,3,3,0,0,0,0,0,0,5,5,5,0,4,6,3,3},{3,3,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,6,3,3},{3,3,6,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,6,3,3},{3,3,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,3,3},{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}}
;

GameMap::GameMap(GameScene *scene, QObject *parent) : QObject(parent)
{
    for(int i=1;i<=NUMX;i++) {
        for(int j=1;j<=NUMY;j++) {
            switch (map[i][j]) {
            case Block::Dirt:
                m_pBlocks[i][j]=new Dirt();
                break;
            case Block::Grass:
                m_pBlocks[i][j]=new Grass();
                break;
            case Block::Stone:
                m_pBlocks[i][j]=new Stone();
                break;
            case Block::Water:
                m_pBlocks[i][j]=new Water();
                break;
            case Block::Lava:
                m_pBlocks[i][j]=new Lava();
                break;
            case Block::GrassPath:
                m_pBlocks[i][j]=new GrassPath();
                break;
            case Block::Ice:
                m_pBlocks[i][j]=new Ice();
                break;
            case Block::NetherPortal:
                m_pBlocks[i][j]=new NetherPortal();
                break;
            }
            m_pBlocks[i][j]->setLogicPos(QPoint(i,j));
            scene->addItem(m_pBlocks[i][j]);
        }
    }
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget) {
    GameItem::paint(painter,option,widget);
}

void Block::onframeChange(int frameCount) {
    Q_UNUSED(frameCount);
    update();
}

//
// Dirt
//

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

//
// Grass
//

Image* Grass::m_image=nullptr;

Grass::Grass(QGraphicsItem *parent):
    Block(parent)
{
//    connect(Grass::m_image, SIGNAL(frameChanged(int)), this, SLOT(onFrameChange(int)));
}

Grass::~Grass(){}

Block::BlockType Grass::blockType() const {
    return Block::Grass;
}

const Image* Grass::image() const {
    return Grass::m_image;
}

//
// Stone
//

Image* Stone::m_image=nullptr;

Stone::Stone(QGraphicsItem *parent):
    Block(parent)
{
//    connect(Stone::m_image, SIGNAL(frameChanged(int)), this, SLOT(onFrameChange(int)));
}

Stone::~Stone(){}

Block::BlockType Stone::blockType() const {
    return Block::Stone;
}

const Image* Stone::image() const {
    return Stone::m_image;
}

//
// Water
//

Image* Water::m_image=nullptr;

Water::Water(QGraphicsItem *parent):
    Block(parent)
{
    connect(Water::m_image, SIGNAL(frameChanged(int)), this, SLOT(onFrameChange(int)));
}

Water::~Water(){}

Block::BlockType Water::blockType() const {
    return Block::Water;
}

const Image* Water::image() const {
    return Water::m_image;
}

//
// Lava
//

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

//
// GrassPath
//

Image* GrassPath::m_image=nullptr;

GrassPath::GrassPath(QGraphicsItem *parent):
    Block(parent)
{
//    connect(GrassPath::m_image, SIGNAL(frameChanged(int)), this, SLOT(onFrameChange(int)));
}

GrassPath::~GrassPath(){}

Block::BlockType GrassPath::blockType() const {
    return Block::GrassPath;
}

const Image* GrassPath::image() const {
    return GrassPath::m_image;
}

//
// Ice
//

Image* Ice::m_image=nullptr;

Ice::Ice(QGraphicsItem *parent):
    Block(parent)
{
//    connect(Ice::m_image, SIGNAL(frameChanged(int)), this, SLOT(onFrameChange(int)));
}

Ice::~Ice(){}

Block::BlockType Ice::blockType() const {
    return Block::Ice;
}

const Image* Ice::image() const {
    return Ice::m_image;
}

//
// NetherPortal
//

Image* NetherPortal::m_image=nullptr;

NetherPortal::NetherPortal(QGraphicsItem *parent):
    Block(parent)
{
    connect(NetherPortal::m_image, SIGNAL(frameChanged(int)), this, SLOT(onFrameChange(int)));
}

NetherPortal::~NetherPortal(){}

Block::BlockType NetherPortal::blockType() const {
    return Block::NetherPortal;
}

const Image* NetherPortal::image() const {
    return NetherPortal::m_image;
}
