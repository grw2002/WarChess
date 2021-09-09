#ifndef MAP_H
#define MAP_H

#include "GameConfig.h"
#include "gameitem.h"
#include "imageinitializer.h"


#include <QObject>

class GameMap : public QObject {
  Q_OBJECT
public:
  explicit GameMap(GameScene *scene, QObject *parent = nullptr);
  Block **operator[](int x) { return m_pBlocks[x]; }

  Block *operator[](QPoint p) { return (*this)[p.x()][p.y()]; }

signals:

private:
  Block *m_pBlocks[NUMX + 2][NUMY + 2];
};

class Block : public GameItem {
  Q_OBJECT
public:
  enum BlockType {
    Dirt = 0,
    Grass = 1,
    Stone = 2,
    Water = 3,
    Lava = 4,
    GrassPath = 5,
    Ice = 6,
    NetherPortal = 7
  };

  explicit Block(QGraphicsItem *parent = nullptr) : GameItem(parent) {
    setZValue(100);
  }

  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) override;

  virtual BlockType blockType() const = 0;

  bool occupation() const { return m_bOccupied; }

  void setOccupation(bool occupied) { m_bOccupied = occupied; }

  Unit *unit() const { return m_unit; }

protected slots:
  void onframeChange(int frameCount);

private:
  bool m_bOccupied;
  Unit *m_unit;
  friend class MapController;
};

// Dirt

class Dirt : public Block {
  Q_OBJECT
public:
  explicit Dirt(QGraphicsItem *parent = nullptr);

  ~Dirt();

  BlockType blockType() const override;

protected:
  const Image *image() const override;

private:
  static Image *m_image;

private:
  friend void ImageInitializer::ImageInitial();
};

// Grass

class Grass : public Block {
  Q_OBJECT
public:
  explicit Grass(QGraphicsItem *parent = nullptr);

  ~Grass();

  BlockType blockType() const override;

protected:
  const Image *image() const override;

private:
  static Image *m_image;

public:
  friend void ImageInitializer::ImageInitial();
};

// Stone

class Stone : public Block {
  Q_OBJECT
public:
  explicit Stone(QGraphicsItem *parent = nullptr);

  ~Stone();

  BlockType blockType() const override;

protected:
  const Image *image() const override;

private:
  static Image *m_image;

public:
  friend void ImageInitializer::ImageInitial();
};

// Water

class Water : public Block {
  Q_OBJECT
public:
  explicit Water(QGraphicsItem *parent = nullptr);

  ~Water();

  BlockType blockType() const override;

protected:
  const Image *image() const override;

private:
  static Image *m_image;

public:
  friend void ImageInitializer::ImageInitial();
};

// Lava

class Lava : public Block {
  Q_OBJECT
public:
  explicit Lava(QGraphicsItem *parent = nullptr);

  ~Lava();

  BlockType blockType() const override;

protected:
  const Image *image() const override;

private:
  static Image *m_image;

public:
  friend void ImageInitializer::ImageInitial();
};

// GrassPath

class GrassPath : public Block {
  Q_OBJECT
public:
  explicit GrassPath(QGraphicsItem *parent = nullptr);

  ~GrassPath();

  BlockType blockType() const override;

protected:
  const Image *image() const override;

private:
  static Image *m_image;

public:
  friend void ImageInitializer::ImageInitial();
};

// Ice

class Ice : public Block {
  Q_OBJECT
public:
  explicit Ice(QGraphicsItem *parent = nullptr);

  ~Ice();

  BlockType blockType() const override;

protected:
  const Image *image() const override;

private:
  static Image *m_image;

public:
  friend void ImageInitializer::ImageInitial();
};

// NetherPortal

class NetherPortal : public Block {
  Q_OBJECT
public:
  explicit NetherPortal(QGraphicsItem *parent = nullptr);

  ~NetherPortal();

  BlockType blockType() const override;

protected:
  const Image *image() const override;

private:
  static Image *m_image;

public:
  friend void ImageInitializer::ImageInitial();
};

#endif // MAP_H
