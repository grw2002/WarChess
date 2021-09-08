#include "action.h"
#include "image.h"
#include "unit.h"
#include "unitcontroller.h"

#include <QPropertyAnimation>

Action::Action(QObject *parent) : QObject(parent)
{

}

Action::~Action() {}

//
// Move Action
//

QPointF LogicToActual(QPoint p) {
    return QPointF((p.x()-0.5)*BLOCK_SIZE,(p.y()-0.5)*BLOCK_SIZE);
}

Move::Move(Unit *unit, QPoint target, std::stack<QPoint> route, QObject *parent):
    Action(parent),
    m_unit(unit),
    m_target(target),
    m_status(Prepare),
    m_route(route),
    m_animation(nullptr)
{
    m_route.pop();
    m_status=Running;
    m_unit->m_status=Unit::Walk;
    NextAnimation();
}

void Move::onAnimationFinish() {
    delete m_animation;
    m_unit->setLogicPos(m_route.top());
    m_route.pop();
    if(m_route.empty()) {
        m_status=End;
        m_unit->m_status=Unit::Hold;
        emit actionFinished();
    } else {
        NextAnimation();
    }
}

void Move::NextAnimation() {
    auto deltaPos=m_route.top()-m_unit->LogicPos();
    if(deltaPos==QPoint(1,0)) {
        m_unit->setDirect(Unit::Right);
    } else if(deltaPos == QPoint(-1,0)) {
        m_unit->setDirect(Unit::Left);
    } else if(deltaPos == QPoint(0,1)) {
        m_unit->setDirect(Unit::Up);
    } else {
        m_unit->setDirect(Unit::Down);
    }
    m_animation=new QPropertyAnimation(m_unit, "pos");
    m_animation->setDuration(300);
    m_animation->setEndValue(LogicToActual(m_route.top()));
    connect(m_animation,SIGNAL(finished()),this,SLOT(onAnimationFinish()));
    m_animation->start();
}

Move::~Move(){}

//
// Attack Action
//

Attack::Attack(QObject *parent):
    Action(parent)
{

}

Attack::~Attack(){}

//
// Bullet
//

Bullet::Bullet(QGraphicsItem *parent):
    GameItem(parent)
{
    ;
}

Bullet::~Bullet() {}

/**
 * @brief Explosion::Explosion
 * @param parent
 */

Explosion::Explosion(QGraphicsItem *parent):
    Bullet(parent)
{
    connect(Explosion::m_image,SIGNAL(frameChanged(int)),this,SLOT(onFrameChange(int)));
}

Explosion::~Explosion() {}

const Image* Explosion::m_image=nullptr;

const Image* Explosion::image() const {
    return m_image;
}
