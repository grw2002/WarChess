#include "level.h"
#include "gameitem.h"
#include "gamemain.h"
#include "gamemap.h"
#include "gamescene.h"
#include "image.h"
#include "unit.h"


#include <QGraphicsTextItem>

Level::Level(GameMain *game, QObject *parent)
    : QObject(parent), m_pGame(game) {}

Level::~Level() { delete m_pMap; }

bool Level::NextStage(GameMain *game, GameMain::GameStatus prev,
                      GameMain::GameStatus nex) {
  Q_UNUSED(game);
  Q_UNUSED(prev);
  Q_UNUSED(nex);
  return false;
}

/**
 * @brief Encounter::Encounter
 * @param scene
 * @param parent
 */

Encounter::Encounter(GameMain *game, QObject *parent) : Level(game, parent) {}

Encounter::~Encounter() {
  auto scene = m_pGame->scene();
  for (auto &unit : m_pGame->m_units) {
    scene->removeItem(unit);
    unit->deleteLater();
  }
  m_pGame->m_units.clear();
}

Level::LevelType Encounter::levelType() const { return Level::Encounter; }

void Encounter::InitMap() {
  auto scene = m_pGame->scene();
  m_pMap = new EncounterMap(scene, this);
}

/**
 * @brief Encounter::ability 定义遭遇战中各种单位的属性
 * @param unitType
 * @return
 */

Ability Encounter::ability(Unit::UnitType unitType) const {
  switch (unitType) {
  case Unit::Steve:
    return Ability({10, 3, 5, 5});
    break;
  case Unit::Golem:
    return Ability({20, 3, 2, 5});
    break;
  case Unit::Zombie:
    return Ability({10, 3, 5, 20});
    break;
  case Unit::Creeper:
    return Ability({6, 5, 5, 30});
    break;
  default: {
    return Ability({0, 0, 0, 0});
  }
  }
}

void Encounter::InitUnit() {
  auto map = m_pMap;
  auto &game = m_pGame;
  auto scene = m_pGame->scene();
  for (int i = 1; i <= NUMX; i++) {
    for (int j = 1; j <= NUMY; j++) {
      auto block = (*map)[i][j];
      // NetherPortal生成敌方
      if (block->blockType() == Block::NetherPortal) {
        Unit *unit;
        if (rand() % 3) { // Zombie
          unit = new Zombie(ability(Unit::Zombie));
        } else { // Creeper
          unit = new Creeper(ability(Unit::Creeper));
        }
        scene->addItem(unit);
        unit->setLogicPos(QPoint(i, j));
        game->m_units.push_back(unit);
        // GrassPath生成我方
      } else if (block->blockType() == Block::GrassPath) {
        Unit *unit;
        if (rand() % 3) { // Steve
          unit = new Steve(ability(Unit::Steve));
        } else { // Golem
          unit = new Golem(ability(Unit::Golem));
        }
        scene->addItem(unit);
        unit->setLogicPos(QPoint(i, j));
        game->m_units.push_back(unit);
      }
    }
  }
}

/**
 * @brief Encounter::VictoryJudge 胜利判定：全灭
 * @return
 */
int Encounter::VictoryJudge() {
  bool self = false, enemy = false;
  for (const auto &unit : m_pGame->m_units) {
    self |= unit->playerType() == Unit::Player;
    enemy |= unit->playerType() == Unit::Enemy;
  }
  if (self && enemy) {
    return 0;
  }
  if (self) {
    emit LevelStateChanged(2);
    return 1;
  } else {
    emit LevelStateChanged(3);
    return 2;
  }
}

/**
 * @brief Assault::Assault
 * @param game
 * @param parent
 */

Assault::Assault(GameMain *game, QObject *parent)
    : Level(game, parent), m_nRoundCount(-1) {}

Assault::~Assault() {
  auto scene = m_pGame->scene();
  for (auto &unit : m_pGame->m_units) {
    scene->removeItem(unit);
    unit->deleteLater();
  }
  m_pGame->m_units.clear();
}

Level::LevelType Assault::levelType() const { return Level::Assault; }

void Assault::InitMap() {
  auto scene = m_pGame->scene();
  m_pMap = new AssaultMap(scene, this);
}

/**
 * @brief Assault::InitUnit 初始的时候生成4个地方和1个玩家
 */

void Assault::InitUnit() {
  auto map = m_pMap;
  auto &game = m_pGame;
  auto scene = m_pGame->scene();
  QPoint villagerPos;
  int nGrasspathCount = 0;
  for (int i = 1; i <= NUMX; i++) {
    for (int j = 1; j <= NUMY; j++) {
      auto block = (*map)[i][j];
      if (block->blockType() == Block::NetherPortal) {
        Unit *unit;
        if (rand() % 3) { // Zombie
          unit = new Zombie(ability(Unit::Zombie));
        } else { // Creeper
          unit = new Creeper(ability(Unit::Creeper));
        }
        scene->addItem(unit);
        unit->setLogicPos(QPoint(i, j));
        game->m_units.push_back(unit);
      } else if (block->blockType() == Block::GrassPath) {
        // 这样的随机策略可以保证所有位置的概率均等
        nGrasspathCount++;
        if (rand() % nGrasspathCount == 0) {
          villagerPos = QPoint(i, j);
        }
      }
    }
  }
  Unit *unit;
  unit = new Villager(ability(Unit::Villager));
  scene->addItem(unit);
  unit->setLogicPos(villagerPos);
  game->m_units.push_back(unit);
}

/**
 * @brief Assault::VictoryJudge
 * 胜利判定，这里只判断失败，胜利判定在nextStage里面（村民死亡即失败）
 * @return
 */

int Assault::VictoryJudge() {
  bool self = false, enemy = false, villager = false;
  for (const auto &unit : m_pGame->m_units) {
    self |= unit->playerType() == Unit::Player;
    enemy |= unit->playerType() == Unit::Enemy;
    villager |= unit->unitType() == Unit::Villager;
  }
  if (self && enemy && villager) {
    return 0;
  } else if (!villager) {
    emit LevelStateChanged(3);
    return 2;
  }
  return 0;
}

/**
 * @brief Assault::ability 村庄保卫战中能力设定
 * @param unitType
 * @return
 */

Ability Assault::ability(Unit::UnitType unitType) const {
  switch (unitType) {
  case Unit::Steve:
    return Ability({10, 3, 3, 3});
    break;
  case Unit::Golem:
    return Ability({20, 3, 1, 2});
    break;
  case Unit::Zombie:
    return Ability({10, 3, 3, 10});
    break;
  case Unit::Creeper:
    return Ability({6, 5, 5, 15});
    break;
  case Unit::Villager:
    return Ability({10, 0, 2, 3});
    break;
  default: {
    return Ability({0, 0, 0, 0});
  }
  }
}

/**
 * @brief Assault::NextStage 这里判定胜利，即成功抵挡10轮进攻
 * @param game
 * @param prev
 * @param nex
 * @return
 */

bool Assault::NextStage(GameMain *game, GameMain::GameStatus prev,
                        GameMain::GameStatus nex) {
  Q_UNUSED(game);
  Q_UNUSED(prev);
  if (nex == GameMain::Self) {
    m_nRoundCount++;
    if (m_nRoundCount >= 10) {
      emit LevelStateChanged(2);
      return true;
    }
    game->m_sidebarInfo->setText(QString("抵挡进攻：") +
                                 QString::number(m_nRoundCount) +
                                 QString("/10"));

    auto map = m_pMap;
    auto &game = m_pGame;
    auto scene = m_pGame->scene();

    // 生成2个敌方
    for (int t = 0; t < 2; t++) {
      QPoint pos;
      int nCount = 0;
      for (int i = 1; i <= NUMX; i++) {
        for (int j = 1; j <= NUMY; j++) {
          auto block = (*map)[i][j];
          if (block->blockType() == Block::NetherPortal &&
              !block->occupation()) {
            // 这样的随机策略可以保证所有位置的概率均等
            nCount++;
            if (rand() % nCount == 0) {
              pos = QPoint(i, j);
            }
          }
        }
      }
      if (!nCount) {
        continue;
      }
      Unit *unit;
      if (rand() % 3) { // Zombie
        unit = new Zombie(ability(Unit::Zombie));
      } else { // Creeper
        unit = new Creeper(ability(Unit::Creeper));
      }
      scene->addItem(unit);
      unit->setLogicPos(pos);
      game->m_units.push_back(unit);
    }
    // 生成1个玩家
    for (int t = 0; t < 1; t++) {
      QPoint pos;
      int nCount = 0;
      for (int i = 1; i <= NUMX; i++) {
        for (int j = 1; j <= NUMY; j++) {
          auto block = (*map)[i][j];
          if (block->blockType() == Block::Grass && !block->occupation()) {
            // 同上，这样的随机策略可以保证所有位置的概率均等
            nCount++;
            if (rand() % nCount == 0) {
              pos = QPoint(i, j);
            }
          }
        }
      }
      if (!nCount) {
        continue;
      }
      Unit *unit;
      if (rand() % 3) { // Steve
        unit = new Steve(ability(Unit::Steve));
      } else { // Golem
        unit = new Golem(ability(Unit::Golem));
      }
      scene->addItem(unit);
      unit->setLogicPos(pos);
      game->m_units.push_back(unit);
    }
  }
  return false;
}

/**
 * @brief StartScreen::StartScreen
 * @param game
 * @param parent
 */

const Image *StartScreen::sm_starticon = nullptr;

StartScreen::StartScreen(GameMain *game, QObject *parent)
    : Level(game, parent) {}

StartScreen::~StartScreen() {}

Level::LevelType StartScreen::levelType() const { return Level::Start; }

void StartScreen::InitMap() {
  auto scene = m_pGame->scene();
  m_pMap = new DefaultMap(scene, this);
}

/**
 * @brief StartScreen::InitUnit 这里不用于生成Unit，而是用于绘制GameUI
 */

void StartScreen::InitUnit() {
  QTransform trans(2, 0, 0, 0, 1, 0, 0, 0, 1);
  QTransform trans2(0.5, 0, 0, 0, 1, 0, 0, 0, 1);
  auto scene = m_pGame->scene();
  // 遭遇战按钮
  m_startEncounter = new GameIcon(new Image("", 48, 48), 4);
  scene->addItem(m_startEncounter);
  m_startEncounter->setLogicPos(QPoint((NUMX >> 1) - 2, 14));
  m_startEncounter->setZValue(500);
  m_startEncounter->setTransform(trans);
  connect(m_startEncounter, SIGNAL(IconClicked(int)), this,
          SLOT(startGame(int)));

  // 遭遇战文字
  m_textEncounter = new QGraphicsSimpleTextItem("遭遇战", m_startEncounter);
  m_textEncounter->setPos(15, 20);
  m_textEncounter->setFont(QFont("黑体", 16, 500));
  m_textEncounter->setBrush(QBrush(Qt::white));
  m_textEncounter->setTransform(trans2);
  m_textEncounter->installSceneEventFilter(m_startEncounter);

  // 村庄保卫战按钮
  m_startAssault = new GameIcon(new Image("", 48, 48), 5);
  scene->addItem(m_startAssault);
  m_startAssault->setLogicPos(QPoint((NUMX >> 1) + 1, 14));
  m_startAssault->setZValue(500);
  m_startAssault->setTransform(trans);
  connect(m_startAssault, SIGNAL(IconClicked(int)), this, SLOT(startGame(int)));

  // 村庄保卫战文字
  m_textAssault = new QGraphicsSimpleTextItem("村庄保卫战", m_startAssault);
  m_textAssault->setPos(4, 20);
  m_textAssault->setFont(QFont("黑体", 16, 500));
  m_textAssault->setBrush(QBrush(Qt::white));
  m_textAssault->setTransform(trans2);
  m_textAssault->installSceneEventFilter(m_startAssault);

  // 大Logo
  m_logo = new Logo();
  scene->addItem(m_logo);
  m_logo->setLogicPos(QPoint(NUMX >> 1, NUMY >> 1));
  m_logo->setZValue(500);
}

/**
 * @brief StartScreen::VictoryJudge 这个函数不应当被调用
 * @return
 */

int StartScreen::VictoryJudge() { return 1; }

/**
 * @brief StartScreen::ability 这个函数不应当被调用
 * @return
 */
Ability StartScreen::ability(Unit::UnitType) const { return Ability(); }

/**
 * @brief StartScreen::startGame 用于接收按钮的回调
 * @param x
 */

void StartScreen::startGame(int x) {
  if (x == 0) {
    return;
  }
  // 做一些必要的清理
  auto scene = m_pGame->scene();
  scene->removeItem(m_startEncounter);
  scene->removeItem(m_startAssault);
  scene->removeItem(m_logo);
  m_startEncounter->deleteLater();
  m_startAssault->deleteLater();
  m_logo->deleteLater();
  m_pGame->m_pOverlayUI = nullptr;
  emit LevelStateChanged(x);
}

/**
 * @brief EndScreen::EndScreen 结束界面
 * @param victory true-获胜，false-失败
 * @param game
 * @param parent
 */

EndScreen::EndScreen(bool victory, GameMain *game, QObject *parent)
    : Level(game, parent), m_bVictory(victory) {}

EndScreen::~EndScreen() {}

const Image *EndScreen::sm_starticon = nullptr;

void EndScreen::InitMap() {
  auto scene = m_pGame->scene();
  m_pMap = new DefaultMap(scene, this);
}

/**
 * @brief EndScreen::InitUnit 这里不用于生成Unit，而是用于绘制GameUI
 */

void EndScreen::InitUnit() {
  QTransform trans(2, 0, 0, 0, 1, 0, 0, 0, 1);
  QTransform trans2(0.5, 0, 0, 0, 1, 0, 0, 0, 1);
  auto scene = m_pGame->scene();

  m_backToHome = new GameIcon(new Image("", 48, 48), 1);
  scene->addItem(m_backToHome);
  m_backToHome->setLogicPos(QPoint((NUMX >> 1), 14));
  m_backToHome->setZValue(500);
  m_backToHome->setTransform(trans);
  connect(m_backToHome, SIGNAL(IconClicked(int)), this, SLOT(backToHome(int)));

  m_textHome = new QGraphicsSimpleTextItem("返回主界面", m_backToHome);
  m_textHome->setPos(4, 20);
  m_textHome->setFont(QFont("黑体", 16, 500));
  m_textHome->setBrush(QBrush(Qt::white));
  m_textHome->setTransform(trans2);
  m_textHome->installSceneEventFilter(m_backToHome);

  m_title = scene->addSimpleText(m_bVictory ? "胜利！" : "失败");
  m_title->setBrush(QBrush(Qt::white));
  m_title->setPos(QPointF(((NUMX >> 1) - 3) * BLOCK_SIZE,
                          ((NUMY >> 1) - 3) * (BLOCK_SIZE)));
  m_title->setFont(QFont("黑体", 144, 500));
  m_title->setZValue(400);
}

/**
 * @brief EndScreen::backToHome 用于接收按钮的回调
 * @param x
 */

void EndScreen::backToHome(int x) {
  if (x == 0) {
    return;
  }
  auto scene = m_pGame->scene();
  scene->removeItem(m_backToHome);
  scene->removeItem(m_textHome);
  scene->removeItem(m_title);
  m_backToHome->deleteLater();
  delete m_textHome;
  delete m_title;
  m_pGame->m_pOverlayUI = nullptr;
  emit LevelStateChanged(x);
}

/**
 * @brief EndScreen::VictoryJudge 这个函数不应当被调用
 * @return
 */

int EndScreen::VictoryJudge() { return 1; }

/**
 * @brief ability 这个函数不应当被调用
 * @return
 */

Ability EndScreen::ability(Unit::UnitType) const { return Ability(); }
