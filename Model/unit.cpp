#include "unit.h"

const QTransform Unit::sm_transLeft(1,0,0,0,1,0,0,0,1);
const QTransform Unit::sm_transRight(-1,0,0,0,1,0,0,0,1);

Unit::Unit(QGraphicsItem *parent) :
    GameItem(parent),
    m_direct(Left),
    m_status(Hold)
{
    setDirect(Right);
}

// Steve

std::unordered_map<Unit::Status, Image*> Steve::sm_images;

Unit::UnitType Steve::unitType() const {
    return Unit::Steve;
}

Unit::PlayerType Steve::playerType() const {
    return Unit::Player;
}

Steve::Steve(QGraphicsItem *parent):
    Unit(parent)
{
    m_image=Steve::sm_images[m_status];
    connect(Steve::sm_images[Walk],SIGNAL(frameChanged(int)),this,SLOT(onFrameChange(int)));
    connect(Steve::sm_images[Attack],SIGNAL(frameChanged(int)),this,SLOT(onFrameChange(int)));
}

Steve::~Steve()
{

}

const Image* Steve::image() const {
    return m_image;
}

// Golem

std::unordered_map<Unit::Status, Image*> Golem::sm_images;

Unit::UnitType Golem::unitType() const {
    return Unit::Golem;
}

Unit::PlayerType Golem::playerType() const {
    return Unit::Player;
}

Golem::Golem(QGraphicsItem *parent):
    Unit(parent)
{
    m_image=Golem::sm_images[m_status];
    connect(Golem::sm_images[Walk],SIGNAL(frameChanged(int)),this,SLOT(onFrameChange(int)));
    connect(Golem::sm_images[Attack],SIGNAL(frameChanged(int)),this,SLOT(onFrameChange(int)));
}

Golem::~Golem()
{

}

const Image* Golem::image() const {
    return m_image;
}

// Zombie

std::unordered_map<Unit::Status, Image*> Zombie::sm_images;

Unit::UnitType Zombie::unitType() const {
    return Unit::Zombie;
}

Unit::PlayerType Zombie::playerType() const {
    return Unit::Enemy;
}

Zombie::Zombie(QGraphicsItem *parent):
    Unit(parent)
{
    m_image=Zombie::sm_images[m_status];
    connect(Zombie::sm_images[Walk],SIGNAL(frameChanged(int)),this,SLOT(onFrameChange(int)));
    connect(Zombie::sm_images[Attack],SIGNAL(frameChanged(int)),this,SLOT(onFrameChange(int)));
}

Zombie::~Zombie()
{

}

const Image* Zombie::image() const {
    return m_image;
}

// Creeper

std::unordered_map<Unit::Status, Image*> Creeper::sm_images;

Unit::UnitType Creeper::unitType() const {
    return Unit::Creeper;
}

Unit::PlayerType Creeper::playerType() const {
    return Unit::Enemy;
}

Creeper::Creeper(QGraphicsItem *parent):
    Unit(parent)
{
    m_image=Creeper::sm_images[m_status];
    connect(Creeper::sm_images[Walk],SIGNAL(frameChanged(int)),this,SLOT(onFrameChange(int)));
    connect(Creeper::sm_images[Attack],SIGNAL(frameChanged(int)),this,SLOT(onFrameChange(int)));
}

Creeper::~Creeper()
{

}

const Image* Creeper::image() const {
    return m_image;
}
