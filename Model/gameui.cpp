#include "gameui.h"
#include "gamecontroller.h"
#include "image.h"
#include "mapcontroller.h"
#include "unit.h"
#include "unitcontroller.h"


#include <QEvent>
#include <QPixmap>


/**
 * @brief GameUI::GameUI
 * @param parent
 */
GameUI::GameUI(QGraphicsItem *parent) : GameItem(parent) {}

GameUI::~GameUI() {}

void GameUI::onClick(QGraphicsSceneMouseEvent *event) { Q_UNUSED(event); }

/**
 * @brief UnitStatus::UnitStatus
 * @param unit
 * @param parent
 */

UnitStatus::UnitStatus(Unit *unit, QGraphicsItem *parent)
    : GameUI(parent), m_unit(unit) {
  setParent(unit);
  setZValue(401);
  auto property = unit->property(), ability = unit->ability();
  m_infoBox = new QGraphicsTextItem(
      QString("类型：") + unitType() + '\n' + QString("生命值：") +
          QString::number(property.hp) + '/' + QString::number(ability.hp) +
          '\n' + QString("攻击力：") + QString::number(property.attack) + '\n' +
          QString("行动力：") + QString::number(property.movable) + '\n' +
          QString("感知力：") + QString::number(property.detection) + '\n' +
          QString("类型：") +
          (unit->playerType() == Unit::Player ? "我方" : "敌军") + '\n',
      this);
  m_infoBox->setPos(50, 50);
  m_infoBox->setFont(QFont("Microsoft Yahei", 13));
}

UnitStatus::~UnitStatus() {}

const Image *UnitStatus::m_book = nullptr;

GameUI::UIType UnitStatus::uiType() const { return GameUI::UnitStatus; }

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
    return "Creeper?Aw~man";
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

/**
 * @brief UnitMove::UnitMove
 * @param unit
 * @param dests
 * @param parent
 */

UnitMove::UnitMove(Unit *unit, std::vector<QPoint> dests, QGraphicsItem *parent)
    : GameUI(parent), m_unit(unit), m_dests(dests) {
  setParent(unit);
  setZValue(400);
}

UnitMove::~UnitMove() {}

GameUI::UIType UnitMove::uiType() const { return GameUI::UnitMove; }

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

/**
 * @brief UnitMove::onClick 选中目的地
 * @param event
 */

void UnitMove::onClick(QGraphicsSceneMouseEvent *event) {
  // 右键表示取消
  if (event->button() == Qt::RightButton) {
    GameController::finishCurrentAction(m_game);
    UnitController::closeGameUI(m_game, this);
    return;
  }
  // 如果点击位置有效，那么开始规划路径
  for (const auto &p : m_dests) {
    if (QRectF((p.x() - 1) * BLOCK_SIZE, (p.y() - 1) * BLOCK_SIZE, BLOCK_SIZE,
               BLOCK_SIZE)
            .contains(event->pos())) {
      if (p == m_unit->LogicPos()) {
        GameController::finishCurrentAction(m_game);
        UnitController::closeGameUI(m_game, this);
        return;
      }
      UnitController::closeGameUI(m_game, this);
      UnitController::startMoveAction(m_game, m_unit, p);
      break;
    }
  }
}

/**
 * @brief UnitMove::boundingRect
 * 行动范围可能编辑全图，所以返回全图作为boundingRect
 * @return
 */
QRectF UnitMove::boundingRect() const {
  return QRectF(0, 0, MAP_WIDTH, MAP_HEIGHT);
}

/**
 * @brief UnitMove::image 不使用统一绘图接口
 * @return
 */
const Image *UnitMove::image() const { return nullptr; }

/**
 * @brief UnitAttack::UnitAttack
 * @param unit
 * @param dests
 * @param targets
 * @param parent
 */

UnitAttack::UnitAttack(Unit *unit, std::vector<QPoint> dests,
                       std::vector<Unit *> targets, QGraphicsItem *parent)
    : GameUI(parent), m_unit(unit), m_range(dests), m_targets(targets) {
  setParent(unit);
  setZValue(400);
}

UnitAttack::~UnitAttack() {}

GameUI::UIType UnitAttack::uiType() const { return GameUI::UnitAttack; }

/**
 * @brief UnitMove::boundingRect
 * 行动范围可能编辑全图，所以返回全图作为boundingRect
 * @return
 */

QRectF UnitAttack::boundingRect() const {
  return QRectF(0, 0, MAP_WIDTH, MAP_HEIGHT);
}

/**
 * @brief UnitMove::image 不使用统一绘图接口
 * @return
 */
const Image *UnitAttack::image() const { return nullptr; }

void UnitAttack::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);
  Q_UNUSED(painter);
  // 画范围
  painter->setBrush(QBrush(QColor(0, 0, 0, 63)));
  for (const auto &p : m_range) {
    if (p == m_unit->LogicPos()) {
      continue;
    }
    painter->drawRect((p.x() - 1) * BLOCK_SIZE, (p.y() - 1) * BLOCK_SIZE,
                      BLOCK_SIZE, BLOCK_SIZE);
  }
  // 画可攻击对象
  painter->setBrush(QBrush(QColor(255, 0, 0, 127)));
  for (const auto &target : m_targets) {
    auto logicPos = target->LogicPos();
    painter->drawRect((logicPos.x() - 1) * BLOCK_SIZE,
                      (logicPos.y() - 1) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
  }
}

/**
 * @brief UnitAttack::onClick 选中攻击对象
 * @param event
 */

void UnitAttack::onClick(QGraphicsSceneMouseEvent *event) {
  if (event->button() == Qt::RightButton ||
      QRectF((m_unit->LogicPos().x() - 1) * BLOCK_SIZE,
             (m_unit->LogicPos().y() - 1) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)
          .contains(event->pos())) {
    GameController::finishCurrentAction(m_game);
    UnitController::closeGameUI(m_game, this);
    return;
  }
  for (const auto &p : m_range) {
    if (QRectF((p.x() - 1) * BLOCK_SIZE, (p.y() - 1) * BLOCK_SIZE, BLOCK_SIZE,
               BLOCK_SIZE)
            .contains(event->pos())) {
      for (const auto &target : m_targets) {
        if (p == target->LogicPos()) {
          auto game = m_game;
          auto unit = m_unit;
          UnitController::closeGameUI(game, this);
          UnitController::startAttackAction(game, unit, target);
          return;
        }
      }
    }
  }
}

/**
 * @brief UnitHP::UnitHP
 * @param unit
 * @param parent
 */

UnitHP::UnitHP(Unit *unit, QGraphicsItem *parent)
    : GameUI(parent), m_unit(unit) {
  setParent(unit);
}

UnitHP::~UnitHP() {}

GameUI::UIType UnitHP::uiType() const { return GameUI::UnitHP; }

/**
 * @brief UnitHP::sm_bounding 血条的尺寸
 */
const QRectF UnitHP::sm_bounding(-20, -5, 40, 10);

QRectF UnitHP::boundingRect() const { return UnitHP::sm_bounding; }

void UnitHP::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);
  if (MapController::blockVisible(m_unit->m_game, m_unit->LogicPos())) {
    painter->setBrush(QBrush(Qt::red));
    painter->drawRect(sm_bounding);
    painter->setBrush(QBrush(Qt::green));
    painter->drawRect(
        QRectF(-20, -5, 40 * m_unit->property().hp / m_unit->ability().hp, 10));
  }
}

/**
 * @brief UnitHP::image 不使用统一绘图接口
 * @return
 */
const Image *UnitHP::image() const { return nullptr; }

/**
 * @brief UnitActionMenu::UnitActionMenu
 * @param unit
 * @param parent
 */

UnitActionMenu::UnitActionMenu(Unit *unit, QGraphicsItem *parent)
    : GameUI(parent), m_unit(unit) {
  setParent(unit);
  setZValue(402);

  int offset = 0;

  // 如果可以移动，那么就画移动
  if (!unit->moved() && !unit->attacked()) {
    GameIcon *icon1 = new GameIcon(sm_walkIcon, 1, this);
    icon1->setPos(16, 16);
    connect(icon1, SIGNAL(IconClicked(int)), this, SLOT(onIconClick(int)));

    auto text1 = new QGraphicsTextItem("行动", this);
    text1->setFont(QFont("Microsoft Yahei", 13));
    text1->setPos(28, 80);

    offset += 80;
  }

  // 如果可以攻击，那么就画攻击
  if (!unit->attacked() && unit->unitType() != Unit::Villager) {
    GameIcon *icon2 = new GameIcon(sm_attackIcon, 2, this);
    icon2->setPos(offset + 16, 16);
    connect(icon2, SIGNAL(IconClicked(int)), this, SLOT(onIconClick(int)));

    auto text2 = new QGraphicsTextItem("攻击", this);
    text2->setFont(QFont("Microsoft Yahei", 13));
    text2->setPos(offset + 28, 80);
  }
}

UnitActionMenu::~UnitActionMenu() {}

GameUI::UIType UnitActionMenu::uiType() const { return GameUI::UnitActionMenu; }

// 各种各样的图标

const Image *UnitActionMenu::sm_backgroundImage = nullptr;
const Image *UnitActionMenu::sm_walkIcon = nullptr;
const Image *UnitActionMenu::sm_attackIcon = nullptr;
const Image *UnitActionMenu::sm_sword = nullptr;
const Image *UnitActionMenu::sm_axe = nullptr;
const Image *UnitActionMenu::sm_tnt = nullptr;

const Image *UnitActionMenu::image() const { return sm_backgroundImage; }

void UnitActionMenu::onIconClick(int nCallback) {
  switch (nCallback) {
  case 1: { // 行动
    auto unit = m_unit;
    auto game = m_game;
    UnitController::closeGameUI(game, this);
    UnitController::prepareMoveAction(game, unit);
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

      auto text1 = new QGraphicsTextItem("用手打", this);
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
  case 3: { // Tap
    auto game = m_game;
    auto unit = m_unit;
    UnitController::closeGameUI(game, this);
    UnitController::prepareAttackAction(game, unit, Attack::Tap);
    break;
  }
  case 4: { // Fireball
    auto game = m_game;
    auto unit = m_unit;
    UnitController::closeGameUI(game, this);
    UnitController::prepareAttackAction(game, unit, Attack::Fireball);
    break;
  }
  case 5: { // Strike
    auto game = m_game;
    auto unit = m_unit;
    UnitController::closeGameUI(game, this);
    UnitController::prepareAttackAction(game, unit, Attack::Strike);
    break;
  }
  default: {
    break;
  }
  }
}

void UnitActionMenu::onClick(QGraphicsSceneMouseEvent *event) {
  if (boundingRect().contains(event->pos())) {
    // 如果没有点中图标但是点中了UI，那么不做任何操作
  } else {
    UnitController::closeGameUI(m_game, this);
  }
}

/**
 * @brief GameIcon::GameIcon
 * @param image 按钮图标
 * @param nCallbackValue
 * @param parent
 */

GameIcon::GameIcon(const Image *image, int nCallbackValue,
                   QGraphicsItem *parent)
    : GameUI(parent), m_image(sm_containerImage2), m_icon(image),
      m_nCallbackValue(nCallbackValue) {
  setAcceptHoverEvents(true);
}

void GameIcon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
  GameUI::paint(painter, option, widget); // 画底
  m_icon->paint(painter, option, widget); // 画图标
}

GameIcon::~GameIcon() {}

const Image *GameIcon::sm_containerImage1 = nullptr;
const Image *GameIcon::sm_containerImage2 = nullptr;

/**
 * @brief GameIcon::image 利用统一绘图接口画按钮的底
 * @return
 */
const Image *GameIcon::image() const { return m_image; }

/**
 * @brief GameIcon::onClick 发出一个信号，返回回调值
 * @param event
 */
void GameIcon::onClick(QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(event);
  emit IconClicked(m_nCallbackValue);
}

GameUI::UIType GameIcon::uiType() const { return GameUI::Icon; }

void GameIcon::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
  m_image = sm_containerImage1;
  GameUI::hoverEnterEvent(event);
}

void GameIcon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
  m_image = sm_containerImage2;
  GameUI::hoverLeaveEvent(event);
}

/**
 * @brief GameIcon::sceneEventFilter
 * 如果要画文字，那么可能会出现重叠，所以需要用sceneEventFilter把点击事件导入到按钮这里来处理
 * @param obj
 * @param e
 * @return
 */

bool GameIcon::sceneEventFilter(QGraphicsItem *obj, QEvent *e) {
  if (e->type() == QEvent::GraphicsSceneMouseRelease) {
    onClick((QGraphicsSceneMouseEvent *)e);
    return true;
  }
  return GameUI::sceneEventFilter(obj, e);
}

/**
 * @brief Logo::Logo 大Logo
 * @param parent
 */

Logo::Logo(QGraphicsItem *parent) : GameUI(parent) {}

Logo::~Logo() {}

GameUI::UIType Logo::uiType() const { return GameUI::Logo; }

const Image *Logo::image() const { return Logo::sm_logo; }

const Image *Logo::sm_logo = nullptr;
