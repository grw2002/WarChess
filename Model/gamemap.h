#ifndef MAP_H
#define MAP_H

#include "GameConfig.h"
#include "gameitem.h"
#include "imageinitializer.h"

#include <QObject>

/**
 * @brief The GameMap class 所有地图的基类
 */
class GameMap : public QObject {
  Q_OBJECT
public:
  explicit GameMap(GameScene *scene, QObject *parent = nullptr);

  virtual ~GameMap();

  /**
   * @brief operator [] 通过下标返回对应Block
   * @param x
   * @return
   */
  Block **operator[](int x);

  /**
   * @brief operator [] 通过logicPos返回对应Block
   * @param p
   * @return
   */
  Block *operator[](QPoint p);

protected:
  GameScene *m_pScene;
  /**
   * @brief initialMap 依据二维数组初始化地图
   * @param map
   */
  void initialMap(const int map[][NUMY + 2]);

private:
  Block *m_pBlocks[NUMX + 2][NUMY + 2];
};

/**
 * @brief The EncounterMap class 遭遇战地图
 */

class EncounterMap : public GameMap {
  Q_OBJECT
public:
  explicit EncounterMap(GameScene *scene, QObject *parent = nullptr);

  ~EncounterMap();

private:
  static const int map[NUMX + 2][NUMY + 2];
};

/**
 * @brief The AssaultMap class 村庄保卫战地图
 */
class AssaultMap : public GameMap {
  Q_OBJECT
public:
  explicit AssaultMap(GameScene *scene, QObject *parent = nullptr);

  ~AssaultMap();

private:
  static const int map[NUMX + 2][NUMY + 2];
};

/**
 * @brief The DefaultMap class 开始界面和结束界面的默认地图
 */

class DefaultMap : public GameMap {
  Q_OBJECT
public:
  explicit DefaultMap(GameScene *scene, QObject *parent = nullptr);

  ~DefaultMap();

private:
  int map[NUMX + 2][NUMY + 2];
};

/**
 * @brief The Block class 所有网格的基类
 */
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

  explicit Block(QGraphicsItem *parent = nullptr);

  /**
   * @brief paint 重载绘图函数，处理网格不可见的情况
   * @param painter
   * @param option
   * @param widget
   */
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) override;

  virtual BlockType blockType() const = 0;

  /**
   * @brief occupation 此方格是否被占用
   * @return
   */
  bool occupation() const;

  /**
   * @brief setOccupation 更改占用情况
   * @param occupied
   */
  void setOccupation(bool occupied);

  /**
   * @brief unit 如果占用，返回占用的单位
   * @return
   */
  Unit *unit() const;

protected slots:
  /**
   * @brief onframeChange 如果地图是动态的gif，需要实时update()以更新
   * @param frameCount
   */
  void onframeChange(int frameCount);

private:
  bool m_bOccupied; //是否被占用
  bool m_bVisible;  //是否可见（战争迷雾）
  Unit *m_unit;     //方格上面的单位
  friend class MapController;
  friend class UnitController;
};

/**
 * @brief The Dirt class
 */

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

/**
 * @brief The Grass class
 */

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

/**
 * @brief The Stone class
 */

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

/**
 * @brief The Water class
 */

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

/**
 * @brief The Lava class
 */

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

/**
 * @brief The GrassPath class
 */

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

/**
 * @brief The Ice class
 */

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

/**
 * @brief The NetherPortal class
 */

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
