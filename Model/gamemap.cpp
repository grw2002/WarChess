#include "gamemap.h"
#include "image.h"

#include <cstdlib>

/**
 * @brief GameMap::GameMap
 * @param scene
 * @param parent
 */

GameMap::GameMap(GameScene *scene, QObject *parent)
    : QObject(parent), m_pScene(scene) {}

GameMap::~GameMap() {
  for (int i = 1; i <= NUMX; i++) {
    for (int j = 1; j <= NUMY; j++) {
      m_pScene->removeItem(m_pBlocks[i][j]);
      m_pBlocks[i][j]->deleteLater();
    }
  }
}

Block **GameMap::operator[](int x) { return m_pBlocks[x]; }

Block *GameMap::operator[](QPoint p) { return (*this)[p.x()][p.y()]; }

void GameMap::initialMap(const int map[][NUMY + 2]) {
  auto scene = m_pScene;
  for (int i = 1; i <= NUMX; i++) {
    for (int j = 1; j <= NUMY; j++) {
      switch (map[i][j]) {
      case Block::Dirt:
        m_pBlocks[i][j] = new Dirt();
        break;
      case Block::Grass:
        m_pBlocks[i][j] = new Grass();
        break;
      case Block::Stone:
        m_pBlocks[i][j] = new Stone();
        break;
      case Block::Water:
        m_pBlocks[i][j] = new Water();
        break;
      case Block::Lava:
        m_pBlocks[i][j] = new Lava();
        break;
      case Block::GrassPath:
        m_pBlocks[i][j] = new GrassPath();
        break;
      case Block::Ice:
        m_pBlocks[i][j] = new Ice();
        break;
      case Block::NetherPortal:
        m_pBlocks[i][j] = new NetherPortal();
        break;
      }
      m_pBlocks[i][j]->setLogicPos(QPoint(i, j));
      scene->addItem(m_pBlocks[i][j]);
    }
  }
}

const int EncounterMap::map[NUMX + 2][NUMY + 2] = {
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
     3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
     3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    {3, 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
     6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 3, 3},
    {3, 3, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
     4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 7, 7, 7, 0, 0, 2, 2, 2,
     0, 4, 0, 0, 0, 0, 0, 0, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 7, 7, 7, 0, 0, 2, 2, 2,
     0, 4, 0, 0, 0, 0, 0, 0, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 7, 7, 7, 0, 0, 2, 2, 2,
     0, 4, 4, 4, 4, 4, 4, 4, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 4, 0, 0, 0, 0, 0, 0, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 4, 0, 0, 0, 0, 0, 0, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 3, 3, 3, 3, 3, 3, 3, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 3, 0, 0, 3, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 3, 0, 0, 3, 0, 0, 0, 0,
     0, 4, 4, 4, 4, 4, 4, 4, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 3, 0, 0, 3, 0, 0, 0, 0,
     0, 0, 0, 0, 4, 0, 0, 0, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 3, 3, 3, 3, 0, 0, 0, 0,
     0, 0, 0, 0, 4, 0, 0, 0, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 4, 0, 0, 0, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 6,
     6, 4, 4, 4, 4, 4, 4, 4, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 3, 3, 3, 3, 3, 3, 3, 6,
     6, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 0, 0, 0, 3, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 0, 0, 3, 0, 3, 0, 0, 0,
     0, 4, 4, 4, 4, 4, 4, 4, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 0, 3, 0, 0, 0, 3, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 4, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 3, 0, 0, 0, 0, 0, 3, 0,
     0, 0, 0, 0, 0, 0, 0, 4, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 4, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 4, 4, 4, 4, 4, 4, 4, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 3, 3, 3, 3, 3, 3, 3, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 0, 0, 0, 0, 0, 0, 3, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 0, 0, 0, 0, 0, 0, 3, 0,
     0, 1, 1, 1, 0, 5, 5, 5, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 0, 0, 0, 0, 0, 0, 3, 0,
     0, 1, 1, 1, 0, 5, 5, 5, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 3, 3, 3, 3, 3, 3, 3, 0,
     0, 1, 1, 1, 0, 5, 5, 5, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 3, 3},
    {3, 3, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
     4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6, 3, 3},
    {3, 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
     6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 3, 3},
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
     3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
     3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}};

EncounterMap::EncounterMap(GameScene *scene, QObject *parent)
    : GameMap(scene, parent) {
  GameMap::initialMap(map);
}

EncounterMap::~EncounterMap() {}

/**
 * @brief Assault::Assault
 * @param scene
 * @param parent
 */

AssaultMap::AssaultMap(GameScene *scene, QObject *parent)
    : GameMap(scene, parent) {
  GameMap::initialMap(map);
}

AssaultMap::~AssaultMap() {}

const int AssaultMap::map[NUMX + 2][NUMY + 2] = {
    {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
     4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
    {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
     4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 7, 0, 0, 4, 4, 0, 0, 0, 6,
     6, 0, 0, 0, 3, 3, 0, 0, 7, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 6,
     6, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 6,
     6, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 6,
     6, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 6,
     6, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 4, 4, 2, 2, 2, 0, 0, 0, 6,
     6, 0, 0, 0, 2, 2, 2, 3, 3, 0, 0, 4, 4},
    {4, 4, 0, 0, 4, 4, 2, 2, 2, 0, 0, 0, 6,
     6, 0, 0, 0, 2, 2, 2, 3, 3, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
     1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
     1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 6, 6, 6, 6, 6, 0, 1, 1, 5,
     5, 1, 1, 0, 6, 6, 6, 6, 6, 0, 0, 4, 4},
    {4, 4, 0, 0, 6, 6, 6, 6, 6, 0, 1, 1, 5,
     5, 1, 1, 0, 6, 6, 6, 6, 6, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
     1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
     1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 3, 3, 2, 2, 2, 0, 0, 0, 6,
     6, 0, 0, 0, 2, 2, 2, 4, 4, 0, 0, 4, 4},
    {4, 4, 0, 0, 3, 3, 2, 2, 2, 0, 0, 0, 6,
     6, 0, 0, 0, 2, 2, 2, 4, 4, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 6,
     6, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 6,
     6, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 6,
     6, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 6,
     6, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 7, 0, 0, 3, 3, 0, 0, 0, 6,
     6, 0, 0, 0, 4, 4, 0, 0, 7, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4},
    {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
     4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
    {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
     4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}};

DefaultMap::DefaultMap(GameScene *scene, QObject *parent)
    : GameMap(scene, parent) {
  for (int i = 0; i < NUMX + 2; i++) {
    for (int j = 0; j < NUMY + 2; j++) {
      map[i][j] = 0;
    }
  }
  GameMap::initialMap(map);
}

DefaultMap::~DefaultMap() {}

/**
 * @brief Block::Block
 * @param parent
 */

Block::Block(QGraphicsItem *parent) : GameItem(parent), m_bOccupied(false) {
  m_bVisible = true;
  setZValue(100);
}

bool Block::occupation() const { return m_bOccupied; }

void Block::setOccupation(bool occupied) { m_bOccupied = occupied; }

Unit *Block::unit() const { return m_unit; }

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
  if (m_bVisible) {
    GameItem::paint(painter, option, widget);
  } else {
    painter->setPen(Qt::transparent);
    painter->setBrush(Qt::black);
    painter->drawRect(-HALF_BLOCK_SIZE, -HALF_BLOCK_SIZE, BLOCK_SIZE,
                      BLOCK_SIZE);
  }
}

void Block::onframeChange(int frameCount) {
  Q_UNUSED(frameCount);
  update();
}

/**
 * @brief Dirt::Dirt
 * @param parent
 */

Dirt::Dirt(QGraphicsItem *parent) : Block(parent) {
  connect(Dirt::m_image, SIGNAL(frameChanged(int)), this,
          SLOT(onFrameChange(int)));
}

Dirt::~Dirt() {}

Image *Dirt::m_image = nullptr;

Block::BlockType Dirt::blockType() const { return Block::Dirt; }

const Image *Dirt::image() const { return Dirt::m_image; }

/**
 * @brief Grass::Grass
 * @param parent
 */

Grass::Grass(QGraphicsItem *parent) : Block(parent) {}

Grass::~Grass() {}

Image *Grass::m_image = nullptr;

Block::BlockType Grass::blockType() const { return Block::Grass; }

const Image *Grass::image() const { return Grass::m_image; }

/**
 * @brief Stone::Stone
 * @param parent
 */

Stone::Stone(QGraphicsItem *parent) : Block(parent) {}

Image *Stone::m_image = nullptr;

Stone::~Stone() {}

Block::BlockType Stone::blockType() const { return Block::Stone; }

const Image *Stone::image() const { return Stone::m_image; }

/**
 * @brief Water::Water
 * @param parent
 */

Water::Water(QGraphicsItem *parent) : Block(parent) {
  connect(Water::m_image, SIGNAL(frameChanged(int)), this,
          SLOT(onFrameChange(int)));
}

Water::~Water() {}

Image *Water::m_image = nullptr;

Block::BlockType Water::blockType() const { return Block::Water; }

const Image *Water::image() const { return Water::m_image; }

/**
 * @brief Lava::Lava
 * @param parent
 */

Lava::Lava(QGraphicsItem *parent) : Block(parent) {
  connect(Lava::m_image, SIGNAL(frameChanged(int)), this,
          SLOT(onFrameChange(int)));
}

Block::BlockType Lava::blockType() const { return Block::Lava; }

Lava::~Lava() {}

Image *Lava::m_image = nullptr;

const Image *Lava::image() const { return Lava::m_image; }

/**
 * @brief GrassPath::GrassPath
 * @param parent
 */

GrassPath::GrassPath(QGraphicsItem *parent) : Block(parent) {}

GrassPath::~GrassPath() {}

Image *GrassPath::m_image = nullptr;

Block::BlockType GrassPath::blockType() const { return Block::GrassPath; }

const Image *GrassPath::image() const { return GrassPath::m_image; }

/**
 * @brief Ice::Ice
 * @param parent
 */

Ice::Ice(QGraphicsItem *parent) : Block(parent) {}

Ice::~Ice() {}

Image *Ice::m_image = nullptr;

Block::BlockType Ice::blockType() const { return Block::Ice; }

const Image *Ice::image() const { return Ice::m_image; }

/**
 * @brief NetherPortal::NetherPortal
 * @param parent
 */

NetherPortal::NetherPortal(QGraphicsItem *parent) : Block(parent) {
  connect(NetherPortal::m_image, SIGNAL(frameChanged(int)), this,
          SLOT(onFrameChange(int)));
}

NetherPortal::~NetherPortal() {}

Image *NetherPortal::m_image = nullptr;

Block::BlockType NetherPortal::blockType() const { return Block::NetherPortal; }

const Image *NetherPortal::image() const { return NetherPortal::m_image; }
