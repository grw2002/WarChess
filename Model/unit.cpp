#include "unit.h"
#include "gamemain.h"
#include "gameui.h"
#include "image.h"
#include "mapcontroller.h"
#include "unitcontroller.h"

const QTransform Unit::sm_transLeft(1, 0, 0, 0, 1, 0, 0, 0, 1);
const QTransform Unit::sm_transRight(-1, 0, 0, 0, 1, 0, 0, 0, 1);

Unit::Unit(QGraphicsItem *parent)
    : GameItem(parent), m_status(Hold), m_direct(Left), m_itemUI(nullptr),
      m_facingRight(false), m_bUnitMoveMenu(false), m_unitMoveMenu(nullptr),
      m_hpBar(new UnitHP(this, this)), m_unitActionUI(nullptr),
      m_unitAttackMenu(nullptr), m_action(nullptr) {
  m_hpBar->setPos(0, HALF_BLOCK_SIZE);
  setDirect(Right);
  setAcceptHoverEvents(true);
  setZValue(300);
  resetRoundState();
}

Unit::~Unit() {
  if (m_itemUI != nullptr) {
    delete m_itemUI;
  }
  if (m_bUnitMoveMenu) {
    delete m_unitMoveMenu;
  }
}

void Unit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *widget) {
  // 战争迷雾
  if (MapController::blockVisible(m_game, LogicPos())) {
    image()->paint(painter, option, widget, m_facingRight);
  }
}

/**
 * @brief Unit::setDirect 用坐标系变换来处理向左/向右变换
 * @param newDirect
 */

void Unit::setDirect(Direct newDirect) {
  m_direct = newDirect;
  if (newDirect == Left) {
    setTransform(sm_transLeft);
  }
  if (newDirect == Right) {
    setTransform(sm_transRight);
  }
  m_hpBar->setTransform(transform());
}

/**
 * @brief Unit::hoverEnterEvent 下面三个函数用于处理UnitStatus
 * @param event
 */

void Unit::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
  if (m_itemUI == nullptr) {
    m_itemUI = new UnitStatus(this);
    m_itemUI->setPos(pos() + (event->pos() * transform()));
    scene()->addItem(m_itemUI);
  }
  GameItem::hoverEnterEvent(event);
}

void Unit::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
  m_itemUI->setPos(pos() + (event->pos() * transform()));
  GameItem::hoverMoveEvent(event);
}

void Unit::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
  if (m_itemUI) {
    scene()->removeItem(m_itemUI);
    m_itemUI = nullptr;
  }
  GameItem::hoverLeaveEvent(event);
}

void Unit::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  if (m_itemUI) {
    m_itemUI->setPos(pos() + (event->pos() * transform()));
  }
  GameItem::mouseMoveEvent(event);
}

/**
 * @brief Unit::onClick 点击处理
 * @param event
 */
void Unit::onClick(QGraphicsSceneMouseEvent *event) {
  if (m_game->actioning()) { // 如果当前有Action，那么不能进行点击事件
    GameItem::onClick(event);
    return;
  }
  if (event->button() != Qt::LeftButton) {
    return;
  }
  if (m_game->status() != GameMain::Self) {
    return;
  }
  if (playerType() == Unit::Player) {
    UnitController::prepareAction(m_game, this, event->pos());
  }
}

/**
 * @brief Unit::setLogicPos 设置逻辑坐标的时候需要处理block的occupation
 * @param pos
 */

void Unit::setLogicPos(QPoint pos) {
  MapController::setOccupation(m_game, this, pos, LogicPos());
  GameItem::setLogicPos(pos);
}

Unit::Direct Unit::direct() const { return m_direct; }

Unit::Status Unit::status() const { return m_status; }

/**
 * @brief Unit::resetRoundState 在进入新的回合时清除移动/攻击记录
 */
void Unit::resetRoundState() {
  m_bMoved = false;
  m_bAttacked = false;
}

bool Unit::moved() { return m_bMoved; }

bool Unit::attacked() { return m_bAttacked; }

/**
 * @brief Steve::Steve
 * @param initialAbility
 * @param parent
 */

Steve::Steve(Ability initialAbility, QGraphicsItem *parent)
    : Unit(parent), m_image(Steve::sm_images[m_status]),
      m_ability(initialAbility), m_property(initialAbility) {
  connect(Steve::sm_images[Walk], SIGNAL(frameChanged(int)), this,
          SLOT(onFrameChange(int)));
  connect(Steve::sm_images[Attack], SIGNAL(frameChanged(int)), this,
          SLOT(onFrameChange(int)));
}

Steve::~Steve() {}

const Ability Steve::ability() const { return m_ability; }

Ability &Steve::property() { return m_property; }

std::unordered_map<Unit::Status, Image *> Steve::sm_images;

Unit::UnitType Steve::unitType() const { return Unit::Steve; }

Unit::PlayerType Steve::playerType() const { return Unit::Player; }

const Image *Steve::image() const { return sm_images[status()]; }

/**
 * @brief Golem::Golem
 * @param initialAbility
 * @param parent
 */

Golem::Golem(Ability initialAbility, QGraphicsItem *parent)
    : Unit(parent), m_ability(initialAbility), m_property(initialAbility) {
  connect(Golem::sm_images[Walk], SIGNAL(frameChanged(int)), this,
          SLOT(onFrameChange(int)));
  connect(Golem::sm_images[Attack], SIGNAL(frameChanged(int)), this,
          SLOT(onFrameChange(int)));
}

Golem::~Golem() {}

const Ability Golem::ability() const { return m_ability; }

Ability &Golem::property() { return m_property; }

std::unordered_map<Unit::Status, Image *> Golem::sm_images;

Unit::UnitType Golem::unitType() const { return Unit::Golem; }

Unit::PlayerType Golem::playerType() const { return Unit::Player; }

const Image *Golem::image() const { return sm_images[status()]; }

/**
 * @brief Zombie::Zombie
 * @param initialAbility
 * @param parent
 */

Zombie::Zombie(Ability initialAbility, QGraphicsItem *parent)
    : Unit(parent), m_ability(initialAbility), m_property(initialAbility) {
  connect(Zombie::sm_images[Walk], SIGNAL(frameChanged(int)), this,
          SLOT(onFrameChange(int)));
  connect(Zombie::sm_images[Attack], SIGNAL(frameChanged(int)), this,
          SLOT(onFrameChange(int)));
}

Zombie::~Zombie() {}

const Ability Zombie::ability() const { return m_ability; }

Ability &Zombie::property() { return m_property; }

std::unordered_map<Unit::Status, Image *> Zombie::sm_images;

Unit::UnitType Zombie::unitType() const { return Unit::Zombie; }

Unit::PlayerType Zombie::playerType() const { return Unit::Enemy; }

const Image *Zombie::image() const { return Zombie::sm_images[status()]; }

/**
 * @brief Creeper::Creeper
 * @param initialAbility
 * @param parent
 */

Creeper::Creeper(Ability initialAbility, QGraphicsItem *parent)
    : Unit(parent), m_ability(initialAbility), m_property(initialAbility) {
  connect(Creeper::sm_images[Walk], SIGNAL(frameChanged(int)), this,
          SLOT(onFrameChange(int)));
  connect(Creeper::sm_images[Attack], SIGNAL(frameChanged(int)), this,
          SLOT(onFrameChange(int)));
}

Creeper::~Creeper() {}

const Ability Creeper::ability() const { return m_ability; }

Ability &Creeper::property() { return m_property; }

std::unordered_map<Unit::Status, Image *> Creeper::sm_images;

Unit::UnitType Creeper::unitType() const { return Unit::Creeper; }

Unit::PlayerType Creeper::playerType() const { return Unit::Enemy; }

const Image *Creeper::image() const { return Creeper::sm_images[m_status]; }

/**
 * @brief Villager::Villager
 * @param initialAbility
 * @param parent
 */

Villager::Villager(Ability initialAbility, QGraphicsItem *parent)
    : Unit(parent), m_ability(initialAbility), m_property(initialAbility) {
  connect(Villager::sm_images[Walk], SIGNAL(frameChanged(int)), this,
          SLOT(onFrameChange(int)));
}

Villager::~Villager() {}

std::unordered_map<Unit::Status, Image *> Villager::sm_images;

Unit::UnitType Villager::unitType() const { return Unit::Villager; }

Unit::PlayerType Villager::playerType() const { return Unit::Player; }

const Image *Villager::image() const { return Villager::sm_images[m_status]; }
