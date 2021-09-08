#include "gameui.h"
#include "unit.h"
#include "image.h"
#include "unitcontroller.h"

#include <QPixmap>

#include <qDebug>

GameUI::GameUI(QGraphicsItem *parent):
    GameItem(parent)
{

}

GameUI::~GameUI(){}

//
// UnitStatus
//

const Image* UnitStatus::m_book=nullptr;

UnitStatus::UnitStatus(Unit *unit, QGraphicsItem *parent):
    GameUI(parent),
    m_unit(unit)
{
    setParent(unit);
    setZValue(400);
    auto ability=unit->ability();
    m_infoBox=new QGraphicsTextItem(QString("类型：")+unitType()+'\n'
                                    +QString("生命值：")+QString::number(ability.hp)+'\n'
                                    +QString("攻击力：")+QString::number(ability.attack)+'\n'
                                    +QString("行动力：")+QString::number(ability.movable)+'\n'
                                    , this);
    m_infoBox->setPos(35,35);
    m_infoBox->setFont(QFont("Microsoft Yahei", 13));
}

UnitStatus::~UnitStatus() {}

void UnitStatus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    GameItem::paint(painter,option,widget);
}

QRectF UnitStatus::boundingRect() const {
    return GameItem::boundingRect();
}

const Image* UnitStatus::image() const {
    return m_book;
}

const char* UnitStatus::unitType() const {
    switch (m_unit->unitType()) {
    case Unit::Steve:
        return "Steve";
        break;
    case Unit::Golem:
        return "Golem";
        break;
    case Unit::Zombie:
        return "Zombie";
        break;
    case Unit::Creeper:
        return "Creeper";
        break;
    case Unit::Villager:
        return "Villager";
        break;
    case Unit::Skeleton:
        return "Skeleton";
        break;
    case Unit::Enderman:
        return "Enderman";
        break;
    }
    return "";
}

void UnitStatus::onClick(QGraphicsSceneMouseEvent *event) {
    ((Unit*)parent())->onClick(event);
}

//
// UnitMove
//

UnitMove::UnitMove(Unit *unit, std::vector<QPoint> dests, QGraphicsItem *parent):
    GameUI(parent),
    m_unit(unit),
    m_dests(dests)
{
    setParent(unit);
    setZValue(200);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

UnitMove::~UnitMove(){}

void UnitMove::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(painter);
    painter->setBrush(QBrush(QColor(255,0,0,100)));
    for(const auto& p: m_dests) {
        if(p==m_unit->LogicPos()) {
            continue;
        }
        painter->drawRect((p.x()-1)*BLOCK_SIZE,(p.y()-1)*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE);
    }
}

void UnitMove::onClick(QGraphicsSceneMouseEvent *event) {
    for(const auto& p: m_dests) {
        if(QRectF((p.x()-1)*BLOCK_SIZE,(p.y()-1)*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE).contains(event->pos())) {
            emit DestSelected(p);
            break;
        }
    }
}
