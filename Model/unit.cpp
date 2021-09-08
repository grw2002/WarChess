#include "unit.h"
#include "gameui.h"
#include "image.h"
#include "gamemain.h"
#include "unitcontroller.h"

const QTransform Unit::sm_transLeft(1,0,0,0,1,0,0,0,1);
const QTransform Unit::sm_transRight(-1,0,0,0,1,0,0,0,1);

Unit::Unit(QGraphicsItem *parent) :
    GameItem(parent),
    m_status(Hold),
    m_direct(Left),
    m_itemUI(nullptr),
    m_facingRight(false),
    m_bUnitMoveMenu(false),
    m_unitMoveMenu(nullptr)
{
    setDirect(Right);
    setAcceptHoverEvents(true);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    setZValue(300);
}

Unit::~Unit() {
    if(m_itemUI!=nullptr) {
        delete m_itemUI;
    }
    if(m_bUnitMoveMenu) {
        delete m_unitMoveMenu;
    }
}

void Unit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) {
    image()->paint(painter,option,widget,m_facingRight);
    painter->setPen(Qt::red);
    painter->drawRect(boundingRect());
}

void Unit::setDirect(Direct newDirect) {
    m_direct=newDirect;
    if(newDirect==Left) {
        setTransform(sm_transLeft);
//            m_facingRight=false;
    }
    if(newDirect==Right) {
        setTransform(sm_transRight);
//            m_facingRight=true;
    }
}

void Unit::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    if(m_itemUI == nullptr) {
        m_itemUI=new UnitStatus(this);
        m_itemUI->setPos(pos()+(event->pos()*transform()));
        scene()->addItem(m_itemUI);
    }
    GameItem::hoverEnterEvent(event);
}

void Unit::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    m_itemUI->setPos(pos()+(event->pos()*transform()));
    GameItem::hoverMoveEvent(event);
}

void Unit::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    if(m_itemUI) {
        scene()->removeItem(m_itemUI);
        m_itemUI=nullptr;
    }
    GameItem::hoverLeaveEvent(event);
}

void Unit::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if(m_itemUI) {
        m_itemUI->setPos(pos()+(event->pos()*transform()));
    }
    GameItem::mouseMoveEvent(event);
}

void Unit::onClick(QGraphicsSceneMouseEvent *event) {
    qDebug()<<"unit click";
    Q_UNUSED(event);
    if(m_bUnitMoveMenu) {
        scene()->removeItem(m_unitMoveMenu);
        m_unitMoveMenu=nullptr;
        m_bUnitMoveMenu=false;
    } else {
        auto dests=UnitController::SPFA(m_game, this);
        m_unitMoveMenu=new UnitMove(this, dests);
        m_unitMoveMenu->setPos(QPointF(0,0));
        scene()->addItem(m_unitMoveMenu);
        m_bUnitMoveMenu=true;
        connect(m_unitMoveMenu,SIGNAL(DestSelected(QPoint)),this,SLOT(onDestSelect(QPoint)));
    }
}

void Unit::onDestSelect(QPoint dest) {
    qDebug()<<"dest "<<dest;
    scene()->removeItem(m_unitMoveMenu);
    m_unitMoveMenu=nullptr;
    m_bUnitMoveMenu=false;
    UnitController::StartMoveAction(m_game,this,dest);
//    auto res=UnitController::FindRoute(m_game,this,dest);
}

//
// Steve
//

std::unordered_map<Unit::Status, Image*> Steve::sm_images;

Steve::UnitType Steve::unitType() const {
    return Unit::Steve;
}

Steve::PlayerType Steve::playerType() const {
    return Unit::Player;
}

Steve::Steve(QGraphicsItem *parent):
    Unit(parent),
    m_image(Steve::sm_images[m_status]),
    m_ability({3,10,5})
{
    connect(Steve::sm_images[Walk],SIGNAL(frameChanged(int)),this,SLOT(onFrameChange(int)));
    connect(Steve::sm_images[Attack],SIGNAL(frameChanged(int)),this,SLOT(onFrameChange(int)));
}

Steve::~Steve()
{

}

const Image* Steve::image() const {
    return sm_images[status()];
}

// Golem

std::unordered_map<Unit::Status, Image*> Golem::sm_images;

Golem::UnitType Golem::unitType() const {
    return Unit::Golem;
}

Golem::PlayerType Golem::playerType() const {
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

Zombie::UnitType Zombie::unitType() const {
    return Unit::Zombie;
}

Zombie::PlayerType Zombie::playerType() const {
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

Creeper::UnitType Creeper::unitType() const {
    return Unit::Creeper;
}

Creeper::PlayerType Creeper::playerType() const {
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
