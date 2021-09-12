#ifndef UNIT_H
#define UNIT_H

#include "GameConfig.h"
#include "gameitem.h"
#include "gameui.h"
#include "imageinitializer.h"

#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QTransform>
#include <unordered_map>

/**
 * @brief The Ability struct Unit的属性
 */
struct Ability {
  int hp;
  int attack;
  int movable;
  int detection;
};

/**
 * @brief The Unit class 所有Unit的基类
 */

class Unit : public GameItem {
  Q_OBJECT
public:
  enum UnitType {
    Zombie = 1,
    Creeper = 2,
    Skeleton = 3,
    Steve = 11,
    Golem = 12,
    Enderman = 13,
    Villager = 14,
  };

  enum PlayerType { Player = 1, Enemy = 2 };

  enum Direct { Up = 1, Down = 2, Left = 3, Right = 4 };

  enum Status { Hold = 1, Walk = 2, Attack = 3 };

  explicit Unit(QGraphicsItem *parent = nullptr);

  virtual ~Unit();

  /**
   * @brief unitType Unit种类
   * @return
   */
  virtual UnitType unitType() const = 0;

  /**
   * @brief playerType 玩家/敌方
   * @return
   */
  virtual PlayerType playerType() const = 0;

  /**
   * @brief setDirect 设置方向（上/下/左/右）
   * @param newDirect
   */
  virtual void setDirect(Direct newDirect);

  virtual Direct direct() const;

  virtual Status status() const;

  /**
   * @brief ability 固有的能力
   * @return
   */
  virtual const Ability ability() const = 0;

  /**
   * @brief property 可能变化的属性（如HP）
   * @return
   */
  virtual Ability &property() = 0;

  virtual void setLogicPos(QPoint) override;

  /**
   * @brief resetRoundState 在进入新的回合时清除移动/攻击记录
   */
  virtual void resetRoundState();

  virtual bool moved();

  virtual bool attacked();

protected:
  virtual void onClick(QGraphicsSceneMouseEvent *event) override;

  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) override;

  virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

  virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;

  virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

protected:
  Status m_status;
  Direct m_direct;

private:
  GameUI *m_itemUI;                                    // UnitStatus
  bool m_facingRight;                                  // 朝向左/右
  const static QTransform sm_transLeft, sm_transRight; // 朝向变换矩阵
  bool m_bUnitMoveMenu; // 是否处于Move菜单模式
  GameUI *m_unitMoveMenu, *m_hpBar, *m_unitActionUI,
      *m_unitAttackMenu;      // 各种菜单
  Action *m_action;           // 当前的action
  bool m_bMoved, m_bAttacked; // 当前回合是否移动/攻击过

  friend class UnitController;
  friend class GameController;
  friend class Move;
  friend class Attack;
  friend class UnitHP;
  friend void UnitStatus::onClick(QGraphicsSceneMouseEvent *event);
};

/**
 * @brief The Steve class
 */

class Steve : public Unit {
  Q_OBJECT
public:
  explicit Steve(Ability initialAbility, QGraphicsItem *parent = nullptr);

  ~Steve();

  UnitType unitType() const override;

  PlayerType playerType() const override;

  const Ability ability() const override;

  Ability &property() override;

protected:
  const Image *image() const override;

private:
  static std::unordered_map<Status, Image *> sm_images; // 状态到图像的映射
  const Image *m_image;
  const struct Ability m_ability;
  struct Ability m_property;

  friend void ImageInitializer::ImageInitial();
};

/**
 * @brief The Golem class
 */

class Golem : public Unit {
  Q_OBJECT
public:
  explicit Golem(Ability initialAbility, QGraphicsItem *parent = nullptr);

  ~Golem();

  UnitType unitType() const override;

  PlayerType playerType() const override;

  const Ability ability() const override;

  Ability &property() override;

protected:
  const Image *image() const override;

private:
  static std::unordered_map<Status, Image *> sm_images; // 状态到图像的映射
  const Image *m_image;
  const struct Ability m_ability;
  struct Ability m_property;

  friend void ImageInitializer::ImageInitial();
};

/**
 * @brief The Zombie class
 */

class Zombie : public Unit {
  Q_OBJECT
public:
  explicit Zombie(Ability initialAbility, QGraphicsItem *parent = nullptr);

  ~Zombie();

  UnitType unitType() const override;

  PlayerType playerType() const override;

  const Ability ability() const override;

  Ability &property() override;

protected:
  const Image *image() const override;

private:
  static std::unordered_map<Status, Image *> sm_images; // 状态到图像的映射
  const Image *m_image;
  const struct Ability m_ability;
  struct Ability m_property;

  friend void ImageInitializer::ImageInitial();
};

/**
 * @brief The Creeper class
 */

class Creeper : public Unit {
  Q_OBJECT
public:
  explicit Creeper(Ability initialAbility, QGraphicsItem *parent = nullptr);

  ~Creeper();

  UnitType unitType() const override;

  PlayerType playerType() const override;

  const Ability ability() const override;

  Ability &property() override;

protected:
  const Image *image() const override;

private:
  static std::unordered_map<Status, Image *> sm_images; // 状态到图像的映射
  const Image *m_image;
  const struct Ability m_ability;
  struct Ability m_property;
  friend void ImageInitializer::ImageInitial();
};

/**
 * @brief The Villager class
 */

class Villager : public Unit {
  Q_OBJECT
public:
  explicit Villager(Ability initialAbility, QGraphicsItem *parent = nullptr);

  ~Villager();

  UnitType unitType() const override;

  PlayerType playerType() const override;

  const Ability ability() const override { return m_ability; }

  Ability &property() override { return m_property; }

protected:
  const Image *image() const override;

private:
  static std::unordered_map<Status, Image *> sm_images; // 状态到图像的映射
  const Image *m_image;
  const struct Ability m_ability;
  struct Ability m_property;
  friend void ImageInitializer::ImageInitial();
};

#endif // UNIT_H
