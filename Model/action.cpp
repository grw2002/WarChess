#include "action.h"
#include "image.h"
#include "mapcontroller.h"
#include "unit.h"
#include "unitcontroller.h"

#include <QPropertyAnimation>

/**
 * @brief Action::Action
 * @param parent
 */

Action::Action(QObject *parent) : QObject(parent) {}

Action::~Action() {}

QPointF LogicToActual(QPoint p) {
  return QPointF((p.x() - 0.5) * BLOCK_SIZE, (p.y() - 0.5) * BLOCK_SIZE);
}

/**
 * @brief Move::Move
 * @param unit
 * @param parent
 */

Move::Move(Unit *unit, QObject *parent)
    : Action(parent), m_unit(unit), m_status(Prepare), m_animation(nullptr) {}

Move::~Move() {}

Unit *Move::unit() const { return m_unit; }

Action::ActionType Move::actionType() const { return Action::Move; }

Action::ActionStatus Move::status() const { return m_status; }

void Move::onAnimationFinish() {
  delete m_animation;
  m_unit->setLogicPos(m_route.top());
  UnitController::adjustZValue(m_unit->m_game);
  m_route.pop();
  if (m_route.empty()) {
    m_status = End;
    m_unit->m_status = Unit::Hold;
    emit actionFinished();
  } else {
    NextAnimation();
  }
}

void Move::NextAnimation() {
  auto deltaPos = m_route.top() - m_unit->LogicPos();
  if (deltaPos == QPoint(1, 0)) {
    m_unit->setDirect(Unit::Right);
  } else if (deltaPos == QPoint(-1, 0)) {
    m_unit->setDirect(Unit::Left);
  } else if (deltaPos == QPoint(0, 1)) {
    m_unit->setDirect(Unit::Up);
  } else {
    m_unit->setDirect(Unit::Down);
  }
  m_animation = new QPropertyAnimation(m_unit, "pos");
  m_animation->setDuration(300);
  m_animation->setEndValue(LogicToActual(m_route.top()));
  connect(m_animation, SIGNAL(finished()), this, SLOT(onAnimationFinish()));
  m_animation->start();
}

void Move::setTarget(QPoint target) { m_target = target; }

void Move::setRoute(const std::stack<QPoint> &route) { m_route = route; }

void Move::start() {
  m_route.pop();
  m_unit->m_status = Unit::Walk;
  m_status = Running;
  NextAnimation();
}

/**
 * @brief Attack::Attack
 * @param unit
 * @param attacktype
 * @param parent
 */

Attack::Attack(Unit *unit, AttackType attacktype, QObject *parent)
    : Action(parent), m_unit(unit), m_target(nullptr), m_attackType(attacktype),
      m_status(Action::Prepare), m_nRound(0), m_explosions(), m_fires(),
      m_animation(nullptr) {}

Attack::~Attack() {}

QSoundEffect *Attack::m_tapSound = nullptr;
QSoundEffect *Attack::m_zombieSound = nullptr;
QSoundEffect *Attack::m_explosionSound = nullptr;
QSoundEffect *Attack::m_creeperSound = nullptr;

void Attack::start() {
  // Tap和Strike同理
  if (attackType() == Attack::Tap || attackType() == Attack::Strike) {
    m_tapSound->play();
    // Unit方向
    if (m_unit->LogicPos().x() < m_target->LogicPos().x()) {
      m_unit->setDirect(Unit::Right);
      m_target->setDirect(Unit::Left);
    } else if (m_unit->LogicPos().x() > m_target->LogicPos().x()) {
      m_unit->setDirect(Unit::Left);
      m_target->setDirect(Unit::Right);
    }
    m_status = Action::Running;
    m_unit->m_status = Unit::Attack;
    m_nTimerId = startTimer(1000);
    m_nRound = 1;
    // Explosion
  } else if (attackType() ==
             Attack::Explosion) { // Assert m_unit->unitType()==Unit::Creeper
    m_creeperSound->play();
    m_status = Action::Running;
    m_unit->m_status = Unit::Attack;
    m_nTimerId = startTimer(1000);
    m_nRound = 1;
    // Fireball
  } else if (attackType() == Attack::Fireball) {
    // Unit方向
    if (m_unit->LogicPos().x() < m_target->LogicPos().x()) {
      m_unit->setDirect(Unit::Right);
    } else if (m_unit->LogicPos().x() > m_target->LogicPos().x()) {
      m_unit->setDirect(Unit::Left);
    }
    // 飞行的火球，animation是运动动画
    Bullet *fire = new Fire();
    fire->setZValue(400);
    m_unit->scene()->addItem(fire);
    fire->setPos(m_unit->pos());
    fire->setScale(0.5);
    m_animation = new QPropertyAnimation(fire, "pos");
    m_animation->setDuration(
        200 * MapController::euclidDistance(m_unit->LogicPos(),
                                            m_target->LogicPos()));
    m_animation->setEndValue(m_target->pos());
    connect(m_animation, SIGNAL(finished()), this, SLOT(onAnimationFinish()));
    m_nRound = 1;
    m_fires.push_back(fire);
    m_animation->start();
  }
}

/**
 * @brief Attack::onAnimationFinish Fireball第一阶段飞行动画结束
 */
void Attack::onAnimationFinish() {
  m_explosionSound->play();
  delete m_animation;
  auto fire = m_fires[0];
  m_unit->scene()->removeItem(fire);
  delete fire;
  m_fires.clear();
  for (int i = 0; i < 10; i++) {
    Bullet *bullet = new class Explosion(m_target);
    bullet->setPos(QPointF(rand() % 64 - 32, rand() % 64 - 32));
    bullet->setScale(rand() % 3 + 1);
    m_explosions.push_back(bullet);
  }
  m_nTimerId = startTimer(1000);
  m_nRound = 2;
}

/**
 * @brief Attack::finish 攻击结束
 */
void Attack::finish() {
  m_tapSound->stop();
  m_status = Action::End;
  if (m_unit) {
    m_unit->m_status = Unit::Hold;
  }
  if (m_target) {
    m_target->m_status = Unit::Hold;
  }
  killTimer(m_nTimerId);
  emit actionFinished();
}

/**
 * @brief Attack::timerEvent
 * Tap、Strike、Explosion、Fireball第二阶段都会涉及timeEvent
 * 但是Fireball第一阶段是通过动画来实现的
 * @param event
 */

void Attack::timerEvent(QTimerEvent *event) {
  Q_UNUSED(event);
  // Tap和Strike
  if (attackType() == Attack::Tap || attackType() == Attack::Strike) {
    if (m_nRound == 2) {
      if (!UnitController::attackSettlement(this)) {
        finish();
        return;
      }
      finish();
    } else if (m_nRound == 1) {
      if (!UnitController::attackSettlement(this)) {
        finish();
        return;
      }
      m_unit->m_status = Unit::Hold;
      if (m_target->unitType() == Unit::Steve ||
          m_target->unitType() == Unit::Golem ||
          m_target->unitType() == Unit::Zombie) {
        m_target->m_status = Unit::Attack;
        m_nRound = 2;
      } else {
        finish();
        return;
      }
    }
    // Explosion的两个阶段
  } else if (attackType() == Attack::Explosion) {
    if (m_nRound == 2) {
      m_explosionSound->stop();
      for (auto &fire : m_fires) {
        m_unit->scene()->removeItem(fire);
        delete fire;
      }
      m_fires.clear();
      for (auto &explosion : m_explosions) {
        m_unit->scene()->removeItem(explosion);
        delete explosion;
      }
      m_explosions.clear();
      UnitController::attackSettlement(this);
      finish();
    } else if (m_nRound == 1) {
      m_creeperSound->stop();
      m_explosionSound->play();
      for (int i = 0; i < 20; i++) {
        Bullet *bullet = new class Explosion(m_unit);
        bullet->setPos(QPointF(rand() % 128 - 64, rand() % 128 - 64));
        bullet->setScale(rand() % 3 + 1);
        m_explosions.push_back(bullet);

        Bullet *fire = new class Fire(m_unit);
        fire->setPos(QPointF(rand() % 128 - 64, rand() % 128 - 64));
        m_fires.push_back(fire);
      }
      m_unit->m_status = Unit::Hold;
      m_nRound = 2;
    }
    // Fireball仅第二阶段
  } else if (attackType() == Attack::Fireball) {
    m_explosionSound->stop();
    for (auto &fire : m_fires) {
      m_unit->scene()->removeItem(fire);
      delete fire;
    }
    m_fires.clear();
    for (auto &explosion : m_explosions) {
      m_unit->scene()->removeItem(explosion);
      delete explosion;
    }
    m_explosions.clear();
    UnitController::attackSettlement(this);
    finish();
  }
}

Action::ActionType Attack::actionType() const { return Action::Attack; }

Action::ActionStatus Attack::status() const { return m_status; }

Attack::AttackType Attack::attackType() const { return m_attackType; }

void Attack::setTarget(Unit *target) { m_target = target; }

Unit *Attack::unit() const { return m_unit; }

/**
 * @brief Bullet::Bullet
 * @param parent
 */

Bullet::Bullet(QGraphicsItem *parent) : GameItem(parent) { ; }

Bullet::~Bullet() {}

/**
 * @brief Explosion::Explosion
 * @param parent
 */

Explosion::Explosion(QGraphicsItem *parent) : Bullet(parent) {
  connect(Explosion::m_image, SIGNAL(frameChanged(int)), this,
          SLOT(onFrameChange(int)));
}

Explosion::~Explosion() {}

Bullet::BulletType Explosion::bulletType() const { return Bullet::Explosion; }

const Image *Explosion::m_image = nullptr;

const Image *Explosion::image() const { return m_image; }

/**
 * @brief Explosion::Explosion
 * @param parent
 */

Fire::Fire(QGraphicsItem *parent) : Bullet(parent) {
  connect(Fire::m_image, SIGNAL(frameChanged(int)), this,
          SLOT(onFrameChange(int)));
}

Fire::~Fire() {}

Bullet::BulletType Fire::bulletType() const { return Bullet::Fire; }

const Image *Fire::m_image = nullptr;

const Image *Fire::image() const { return m_image; }
