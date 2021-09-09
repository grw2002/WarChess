#include "gameui.h"
#include "image.h"
#include "unit.h"
#include "unitcontroller.h"


#include <QPixmap>

#include <qDebug>

GameUI::GameUI(QGraphicsItem *parent) : GameItem(parent) {}

GameUI::~GameUI() {}

//
// UnitStatus
//

const Image *UnitStatus::m_book = nullptr;

UnitStatus::UnitStatus(Unit *unit, QGraphicsItem *parent)
    : GameUI(parent), m_unit(unit) {
  setParent(unit);
  setZValue(401);
  auto property = unit->property(), ability = unit->ability();
  m_infoBox = new QGraphicsTextItem(
      QString("类型：") + unitType() + '\n' + QString("生命值：") +
          QString::number(property.hp) + '/' + QString::number(ability.hp) +
          '\n' + QString("攻击力：") + QString::number(property.attack) + '/' +
          QString::number(ability.attack) + '\n' + QString("行动力：") +
          QString::number(property.movable) + '/' +
          QString::number(ability.movable) + '\n',
      this);
  m_infoBox->setPos(35, 35);
  m_infoBox->setFont(QFont("Microsoft Yahei", 13));
}

UnitStatus::~UnitStatus() {}

void UnitStatus::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) {
  GameItem::paint(painter, option, widget);
}

QRectF UnitStatus::boundingRect() const { return GameItem::boundingRect(); }

const Image *UnitStatus::image() const { return m_book; }

const char *UnitStatus::unitType() const {
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
  event->setPos(event->pos() + pos());
  ((Unit *)parent())->onClick(event);
}

//
// UnitMove
//

UnitMove::UnitMove(Unit *unit, std::vector<QPoint> dests, QGraphicsItem *parent)
    : GameUI(parent), m_unit(unit), m_dests(dests) {
  setParent(unit);
  setZValue(400);
  //    setFlag(QGraphicsItem::ItemIsSelectable);
}

UnitMove::~UnitMove() {}

void UnitMove::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);
  Q_UNUSED(painter);
  painter->setBrush(QBrush(QColor(0, 255, 0, 63)));
  for (const auto &p : m_dests) {
    if (p == m_unit->LogicPos()) {
      continue;
    }
    painter->drawRect((p.x() - 1) * BLOCK_SIZE, (p.y() - 1) * BLOCK_SIZE,
                      BLOCK_SIZE, BLOCK_SIZE);
  }
  painter->setBrush(QBrush(QColor(255, 255, 0, 127)));
  painter->drawRect((m_unit->LogicPos().x() - 1) * BLOCK_SIZE,
                    (m_unit->LogicPos().y() - 1) * BLOCK_SIZE, BLOCK_SIZE,
                    BLOCK_SIZE);
}

void UnitMove::onClick(QGraphicsSceneMouseEvent *event) {
  qDebug() << event->button();
  if (event->button() == Qt::RightButton) {
    UnitController::FinishCurrentAction(m_game);
    //        emit GameUIClosed(this);
    UnitController::CloseGameUI(m_game, this);
    return;
  }
  for (const auto &p : m_dests) {
    if (QRectF((p.x() - 1) * BLOCK_SIZE, (p.y() - 1) * BLOCK_SIZE, BLOCK_SIZE,
               BLOCK_SIZE)
            .contains(event->pos())) {
      if (p == m_unit->LogicPos()) {
        UnitController::FinishCurrentAction(m_game);
        //                emit GameUIClosed(this);
        UnitController::CloseGameUI(m_game, this);
        return;
      }
      //            emit DestSelected(p);
      //            emit GameUIClosed(this);
      UnitController::CloseGameUI(m_game, this);
      UnitController::StartMoveAction(m_game, m_unit, p);
      break;
    }
  }
}

//
// UnitAttack
//

UnitAttack::UnitAttack(Unit *unit, std::vector<QPoint> dests,
                       std::vector<Unit *> targets, QGraphicsItem *parent)
    : GameUI(parent), m_unit(unit), m_range(dests), m_targets(targets) {
  setParent(unit);
  setZValue(400);
  //    setFlag(QGraphicsItem::ItemIsSelectable);
}

UnitAttack::~UnitAttack() {}

void UnitAttack::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);
  Q_UNUSED(painter);
  painter->setBrush(QBrush(QColor(0, 0, 0, 63)));
  for (const auto &p : m_range) {
    if (p == m_unit->LogicPos()) {
      continue;
    }
    painter->drawRect((p.x() - 1) * BLOCK_SIZE, (p.y() - 1) * BLOCK_SIZE,
                      BLOCK_SIZE, BLOCK_SIZE);
  }
  painter->setBrush(QBrush(QColor(255, 0, 0, 127)));
  for (const auto &target : m_targets) {
    auto logicPos = target->LogicPos();
    painter->drawRect((logicPos.x() - 1) * BLOCK_SIZE,
                      (logicPos.y() - 1) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
  }
}

void UnitAttack::onClick(QGraphicsSceneMouseEvent *event) {
  qDebug() << event->button();
  if (event->button() == Qt::RightButton ||
      QRectF((m_unit->LogicPos().x() - 1) * BLOCK_SIZE,
             (m_unit->LogicPos().y() - 1) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)
          .contains(event->pos())) {
    UnitController::FinishCurrentAction(m_game);
    UnitController::CloseGameUI(m_game, this);
    return;
  }
  for (const auto &p : m_range) {
    if (QRectF((p.x() - 1) * BLOCK_SIZE, (p.y() - 1) * BLOCK_SIZE, BLOCK_SIZE,
               BLOCK_SIZE)
            .contains(event->pos())) {
      for (const auto &target : m_targets) {
        if (p == target->LogicPos()) {
          qDebug() << "confirm attack";
          auto game = m_game;
          auto unit = m_unit;
          UnitController::CloseGameUI(game, this);
          UnitController::StartAttackAction(game, unit, target);
          return;
        }
      }
    }
  }
}

//
// UnitHP
//

const QRectF UnitHP::sm_bounding(-20, -5, 40, 10);

UnitHP::UnitHP(Unit *unit, QGraphicsItem *parent)
    : GameUI(parent), m_unit(unit) {
  setParent(unit);
}

UnitHP::~UnitHP() {}

QRectF UnitHP::boundingRect() const { return UnitHP::sm_bounding; }

void UnitHP::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);
  painter->setBrush(QBrush(Qt::red));
  painter->drawRect(sm_bounding);
  painter->setBrush(QBrush(Qt::green));
  painter->drawRect(
      QRectF(-20, -5, 40 * m_unit->property().hp / m_unit->ability().hp, 10));
}

//
// UnitAction
//

const Image *UnitActionMenu::sm_backgroundImage = nullptr;
const Image *UnitActionMenu::sm_walkIcon = nullptr;
const Image *UnitActionMenu::sm_attackIcon = nullptr;
const Image *UnitActionMenu::sm_sword = nullptr;
const Image *UnitActionMenu::sm_axe = nullptr;
const Image *UnitActionMenu::sm_tnt = nullptr;

UnitActionMenu::UnitActionMenu(Unit *unit, QGraphicsItem *parent)
    : GameUI(parent), m_unit(unit) {
  setParent(unit);
  setZValue(402);

  GameIcon *icon1 = new GameIcon(sm_walkIcon, 1, this);
  icon1->setPos(16, 16);
  connect(icon1, SIGNAL(IconClicked(int)), this, SLOT(onIconClick(int)));

  auto text1 = new QGraphicsTextItem("行动", this);
  text1->setFont(QFont("Microsoft Yahei", 13));
  text1->setPos(28, 80);

  GameIcon *icon2 = new GameIcon(sm_attackIcon, 2, this);
  icon2->setPos(16 + 64 + 16, 16);
  connect(icon2, SIGNAL(IconClicked(int)), this, SLOT(onIconClick(int)));

  auto text2 = new QGraphicsTextItem("攻击", this);
  text2->setFont(QFont("Microsoft Yahei", 13));
  text2->setPos(28 + 80, 80);
}

UnitActionMenu::~UnitActionMenu() {}

void UnitActionMenu::onIconClick(int nCallback) {
  qDebug() << "callback " << nCallback;
  switch (nCallback) {
  case 1: { // 行动
    auto unit = m_unit;
    auto game = m_game;
    UnitController::CloseGameUI(game, this);
    UnitController::PrepareMoveAction(game, unit);
    break;
  }
  case 2: { // 攻击
    auto items = childItems();
    for (auto item : items) {
      scene()->removeItem(item);
    }
    switch (m_unit->unitType()) {
    case Unit::Steve: {
      GameIcon *icon1 = new GameIcon(sm_sword, 3, this);
      icon1->setPos(16, 16);
      connect(icon1, SIGNAL(IconClicked(int)), this, SLOT(onIconClick(int)));

      auto text1 = new QGraphicsTextItem("用手撸", this);
      text1->setFont(QFont("Microsoft Yahei", 13));
      text1->setPos(18, 80);

      GameIcon *icon2 = new GameIcon(sm_tnt, 4, this);
      icon2->setPos(16 + 64 + 16, 16);
      connect(icon2, SIGNAL(IconClicked(int)), this, SLOT(onIconClick(int)));

      auto text2 = new QGraphicsTextItem("扔炸弹", this);
      text2->setFont(QFont("Microsoft Yahei", 13));
      text2->setPos(18 + 80, 80);
      break;
    }
    case Unit::Golem: {
      GameIcon *icon1 = new GameIcon(sm_axe, 5, this);
      icon1->setPos(16, 16);
      connect(icon1, SIGNAL(IconClicked(int)), this, SLOT(onIconClick(int)));

      auto text1 = new QGraphicsTextItem("重击", this);
      text1->setFont(QFont("Microsoft Yahei", 13));
      text1->setPos(28, 80);
      break;
    }
    default: {
      break;
    }
    }
    break;
  }
  case 3: { // sword
    auto game = m_game;
    auto unit = m_unit;
    UnitController::CloseGameUI(game, this);
    UnitController::PrepareAttackAction(game, unit, Attack::Tap);
    break;
  }
  case 4: { // fireball
    auto game = m_game;
    auto unit = m_unit;
    UnitController::CloseGameUI(game, this);
    UnitController::PrepareAttackAction(game, unit, Attack::Fireball);
    break;
  }
  case 5: { // axe
    auto game = m_game;
    auto unit = m_unit;
    UnitController::CloseGameUI(game, this);
    UnitController::PrepareAttackAction(game, unit, Attack::Strike);
    break;
  }
  default: {
    break;
  }
  }
}

void UnitActionMenu::onClick(QGraphicsSceneMouseEvent *event) {
  qDebug() << "UnitAction onclick" << event->pos();
  if (boundingRect().contains(event->pos())) {
    qDebug() << "contains";
  } else {
    //        qDebug()<<"emit close";
    //        emit GameUIClosed(this);
    UnitController::CloseGameUI(m_game, this);
  }
}

//
// GameIcon
//

const Image *GameIcon::sm_containerImage1 = nullptr;
const Image *GameIcon::sm_containerImage2 = nullptr;

GameIcon::GameIcon(const Image *image, int nCallbackValue,
                   QGraphicsItem *parent)
    : GameUI(parent), m_icon(image), m_nCallbackValue(nCallbackValue) {}

void GameIcon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
  GameUI::paint(painter, option, widget);
  m_icon->paint(painter, option, widget);
}

GameIcon::~GameIcon() {}
