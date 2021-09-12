#ifndef ACTION_H
#define ACTION_H

#include "GameConfig.h"
#include "gameitem.h"
#include "imageinitializer.h"
#include "soundinitializer.h"

#include <QObject>
#include <QPropertyAnimation>
#include <QSoundEffect>
#include <stack>


class Unit;

/**
 * @brief 所有Action的基类
 */
class Action : public QObject {
  Q_OBJECT
public:
  enum ActionType { Move = 1, Attack = 2 };

  enum ActionStatus { Prepare = 1, Running = 2, End = 3 };

  explicit Action(QObject *parent = nullptr);

  virtual ~Action();

  virtual ActionType actionType() const = 0;

  virtual ActionStatus status() const = 0;

  virtual void start() = 0;

  virtual Unit *unit() const = 0;

signals:
  void actionFinished();
};

/**
 * @brief 移动类
 */
class Move : public Action {
  Q_OBJECT
public:
  explicit Move(Unit *unit, QObject *parent = nullptr);

  ~Move();

  ActionType actionType() const override;

  ActionStatus status() const override;

  /**
   * @brief setTarget 设置目的地
   * @param target
   */
  void setTarget(QPoint target);

  /**
   * @brief setRoute 设置路线
   * @param route
   */
  void setRoute(const std::stack<QPoint> &route);

  void start() override;

  Unit *unit() const override;

public slots:
  /**
   * @brief onAnimationFinish 没走一格就是一次动画，所以对应着一次动画结束
   */
  void onAnimationFinish();

private:
  /**
   * @brief NextAnimation 进行下一步
   */
  void NextAnimation();

private:
  Unit *const m_unit;
  QPoint m_target;
  ActionStatus m_status;
  std::stack<QPoint> m_route;
  QPropertyAnimation *m_animation;
  friend class UnitController;
  friend class GameController;
};

class Attack : public Action {
  Q_OBJECT
public:
  enum AttackType { Tap = 1, Fireball = 2, Strike = 3, Explosion = 4 };

  explicit Attack(Unit *unit, AttackType attacktype, QObject *parent = nullptr);

  ~Attack();

  ActionType actionType() const override;

  ActionStatus status() const override;

  AttackType attackType() const;

  void setTarget(Unit *target);

  void start() override;

  void finish();

  Unit *unit() const override;

public slots:
  void onAnimationFinish();

protected:
  void timerEvent(QTimerEvent *event) override;

private:
  Unit *m_unit, *m_target;
  const AttackType m_attackType;
  ActionStatus m_status;
  int m_nTimerId;
  int m_nRound;
  std::vector<Bullet *> m_explosions, m_fires;
  QPropertyAnimation *m_animation;

  static QSoundEffect *m_tapSound, *m_zombieSound, *m_explosionSound,
      *m_creeperSound;

  friend class UnitController;
  friend class GameController;
  friend class SoundInitializer;
};

/**
 * @brief The Bullet class 所有子弹的基类：Explosion或Fire
 */
class Bullet : public GameItem {
  Q_OBJECT
public:
  enum BulletType { Explosion = 1, Fire = 2 };

  explicit Bullet(QGraphicsItem *parent = nullptr);

  virtual ~Bullet();

  virtual BulletType bulletType() const = 0;
};

class Explosion : public Bullet {
  Q_OBJECT
public:
  explicit Explosion(QGraphicsItem *parent = nullptr);

  ~Explosion();

  BulletType bulletType() const override;

private:
  static const Image *m_image; // 爆炸动画
  const Image *image() const override;
  friend void ImageInitializer::ImageInitial();
};

class Fire : public Bullet {
  Q_OBJECT
public:
  explicit Fire(QGraphicsItem *parent = nullptr);

  ~Fire();

  BulletType bulletType() const override;

private:
  static const Image *m_image; // 火球动画
  const Image *image() const override;
  friend void ImageInitializer::ImageInitial();
};

#endif // ACTION_H
