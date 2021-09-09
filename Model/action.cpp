#include "action.h"
#include "image.h"
#include "mapcontroller.h"
#include "unit.h"
#include "unitcontroller.h"


#include <QPropertyAnimation>

Action::Action(QObject *parent) : QObject(parent) {}

Action::~Action() {}

//
// Move Action
//

QPointF LogicToActual(QPoint p) {
  return QPointF((p.x() - 0.5) * BLOCK_SIZE, (p.y() - 0.5) * BLOCK_SIZE);
}

Move::Move(Unit *unit, QObject *parent)
    : Action(parent), m_unit(unit), m_status(Prepare), m_animation(nullptr) {}

void Move::onAnimationFinish() {
  delete m_animation;
  m_unit->setLogicPos(m_route.top());
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

Move::~Move() {}

void Move::setTarget(QPoint target) { m_target = target; }

void Move::setRoute(const std::stack<QPoint> &route) { m_route = route; }

void Move::start() {
  m_route.pop();
  m_unit->m_status = Unit::Walk;
  m_status = Running;
  NextAnimation();
}

//
// Attack Action
//

Attack::Attack(Unit *unit, AttackType attacktype, QObject *parent)
    : Action(parent), m_unit(unit), m_target(nullptr), m_attackType(attacktype),
      m_status(Action::Prepare) {}

Attack::~Attack() {}

void Attack::start() {
  if (m_unit->LogicPos().x() < m_target->LogicPos().x()) {
    m_unit->setDirect(Unit::Right);
    m_target->setDirect(Unit::Left);
  } else if (m_unit->LogicPos().x() > m_target->LogicPos().x()) {
    m_unit->setDirect(Unit::Left);
    m_target->setDirect(Unit::Right);
  }
  m_unit->setZValue(310);
  m_status = Action::Running;
  m_unit->m_status = Unit::Attack;
  m_nTimerId = startTimer(2000);
  m_bAttackBack = false;
}

void Attack::timerEvent(QTimerEvent *event) {
  if (m_bAttackBack) {
    m_target->setZValue(300);
    killTimer(m_nTimerId);
    m_status = Action::End;
    m_target->m_status = Unit::Hold;
    emit actionFinished();
  } else {
    m_bAttackBack = true;
    m_unit->setZValue(300);
    m_unit->m_status = Unit::Hold;
    m_target->m_status = Unit::Attack;
    m_target->setZValue(310);
  }
}

//
// Bullet
//

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

const Image *Explosion::m_image = nullptr;

const Image *Explosion::image() const { return m_image; }
