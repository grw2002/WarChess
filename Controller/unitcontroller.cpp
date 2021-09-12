#include "unitcontroller.h"
#include "action.h"
#include "gamecontroller.h"
#include "gamemain.h"
#include "gamemap.h"
#include "level.h"
#include "mapcontroller.h"
#include "unit.h"


#include <QHash>
#include <QHashIterator>
#include <QObject>
#include <QPair>
#include <algorithm>
#include <queue>


void UnitController::prepareAction(GameMain *game, Unit *unit, QPointF pos) {
  auto &menu = unit->m_unitActionUI;
  menu = new UnitActionMenu(unit);
  game->scene()->addItem(menu);
  menu->setPos(pos);
  game->m_bAction = true;
  game->m_pOverlayUI = menu;
}

void UnitController::prepareMoveAction(GameMain *game, Unit *unit) {
  int movable = unit->property().movable;
  auto map = game->m_pLevel->m_pMap;
  auto blocktype = (*map)[unit->LogicPos()]->blockType();
  // 特殊方块
  if (blocktype == Block::Grass) {
    movable += 2;
  }
  auto dests = MapController::spfa(game, unit, movable); // 搜索可达范围
  for (auto it = dests.begin(); it != dests.end(); it++) {
    if (!((*map)[*it]->m_bVisible)) {
      dests.erase(it);
      it--;
    }
  }
  auto &menu = unit->m_unitMoveMenu;
  menu = new UnitMove(unit, dests);
  menu->setPos(QPointF(0, 0));
  game->scene()->addItem(menu);
  unit->m_bUnitMoveMenu = true;
  unit->m_action = game->m_pCurrentAction = new Move(unit, game);
  game->m_bAction = true;
  game->m_pOverlayUI = menu;
}

void UnitController::prepareEnemyMoveAction(GameMain *game, Unit *unit) {
  auto dests = MapController::spfa(game, unit,
                                   unit->property().detection); // 搜索可达范围
  unit->m_action = game->m_pCurrentAction = new Move(unit, game);
  game->m_bAction = true;

  const auto map = game->m_pLevel->m_pMap;
  auto target = dests[rand() % dests.size()];
  // 敌方AI：向玩家靠近
  for (const auto &dest : dests) {
    for (int i = 0; i < 4; i++) {
      auto x = dest + MapController::sm_directions[i];
      auto block = (*map)[x];
      if (block->occupation() && block->unit()->playerType() == Unit::Player) {
        target = dest;
      }
    }
  }
  if (target != unit->LogicPos()) {
    startMoveAction(game, unit, target);
  } else {
    // 动不了，直接结束
    unit->m_bMoved = true;
    GameController::finishCurrentAction(game);
  }
}

void UnitController::startMoveAction(GameMain *game, Unit *unit, QPoint dest) {
  auto route = MapController::findRoute(game, unit, dest); // 寻路

  auto *map = game->m_pLevel->m_pMap;
  int movable = unit->property().movable;
  if (unit->playerType() == Unit::Enemy) {
    if ((*map)[unit->LogicPos()]->blockType() == Block::Stone) {
      movable += 2;
    }
  }
  if (unit->playerType() == Unit::Player) {
    if ((*map)[unit->LogicPos()]->blockType() == Block::Grass) {
      movable += 2;
    }
  }

  /**
   * For enemies, the route would be beyonod its movability
   * This could make AI smarter :-)
   */
  if (route.size() > (size_t)(movable + 1)) {
    std::stack<QPoint> st;
    for (int i = 0; i <= movable && !route.empty(); i++) {
      st.push(route.top());
      if ((*map)[route.top()]->blockType() == Block::Ice) {
        i--;
      }
      route.pop();
    }
    while (!route.empty()) {
      route.pop();
    }
    while (!st.empty()) {
      route.push(st.top());
      st.pop();
    }
  }
  Move *action = (Move *)(game->m_pCurrentAction);
  action->setTarget(dest);
  action->setRoute(route);
  QObject::connect(action, SIGNAL(actionFinished()), game,
                   SLOT(onActionFinish()));
  action->start();
}

void UnitController::prepareAttackAction(GameMain *game, Unit *unit,
                                         Attack::AttackType type) {
  auto map = game->m_pLevel->m_pMap;
  std::vector<QPoint> range;
  std::vector<Unit *> targets;
  switch (type) {
  // 这两者都是物攻，所以一起处理
  case Attack::Tap:
  case Attack::Strike: {
    auto pos = unit->LogicPos();
    // 只能打前后左右
    for (int i = 0; i < 4; i++) {
      auto x = pos + MapController::sm_directions[i];
      if (!MapController::posLegal(x)) {
        continue;
      }
      auto block = (*map)[x];
      if (!block->m_bVisible) {
        continue;
      }
      range.push_back(x);
      if (block->occupation()) {
        if (block->unit()->playerType() != unit->playerType()) {
          targets.push_back(block->unit());
        }
      }
    }
    break;
  }
  case Attack::Fireball: {
    auto pos = unit->LogicPos();
    double dist = unit->property().detection;
    for (int i = pos.x() - dist; i <= pos.x() + dist; i++) {
      for (int j = pos.y() - dist; j <= pos.y() + dist; j++) {
        if (!MapController::posLegal(QPoint(i, j))) {
          continue;
        }
        // 用欧氏距离，攻击范围为圆
        if (MapController::euclidDistance(QPoint(i, j), unit->LogicPos()) <=
            dist) {
          auto block = (*map)[i][j];
          if (!block->m_bVisible) {
            continue;
          }
          range.push_back(QPoint(i, j));
          if (block->occupation()) {
            if (block->unit()->playerType() != unit->playerType()) {
              targets.push_back(block->unit());
            }
          }
        }
      }
    }
    break;
  }
  default: {
    break;
  }
  }
  auto menu = unit->m_unitAttackMenu;
  menu = new UnitAttack(unit, range, targets);
  menu->setPos(QPoint(0, 0));
  game->scene()->addItem(menu);
  game->m_pOverlayUI = menu;

  unit->m_action = game->m_pCurrentAction = new Attack(unit, type, game);
  game->m_bAction = true;
}

void UnitController::prepareEnemyAttackAction(GameMain *game, Unit *unit) {
  auto map = game->m_pLevel->m_pMap;
  switch (unit->unitType()) {
  case Unit::Zombie: {
    // 只能打前后左右
    for (int i = 0; i < 4; i++) {
      auto x = unit->LogicPos() + MapController::sm_directions[i];
      auto block = (*map)[x];
      if (block->occupation() && block->unit()->playerType() == Unit::Player) {
        unit->m_action = game->m_pCurrentAction =
            new Attack(unit, Attack::Tap, game);
        game->m_bAction = true;
        startAttackAction(game, unit, block->unit());
        return;
      }
    }
    unit->m_bAttacked = true;
    GameController::finishCurrentAction(game);
    return;
    break;
  }
  case Unit::Creeper: {
    // 游戏设定：Creeper只有在接触玩家的时候会爆炸
    for (int i = 0; i < 4; i++) {
      auto x = unit->LogicPos() + MapController::sm_directions[i];
      auto block = (*map)[x];
      if (block->occupation() && block->unit()->playerType() == Unit::Player) {
        unit->m_action = game->m_pCurrentAction =
            new Attack(unit, Attack::Explosion, game);
        game->m_bAction = true;
        startAttackAction(game, unit, nullptr);
        return;
      }
    }
    unit->m_bAttacked = true;
    GameController::finishCurrentAction(game);
    break;
  }
  default: {
    break;
  }
  }
}

void UnitController::startAttackAction(GameMain *game, Unit *unit,
                                       Unit *target) {
  Q_UNUSED(unit);
  Attack *action = (Attack *)game->m_pCurrentAction;
  action->setTarget(target);
  // Explosion是AOE，没有特定的target
  if (target) {
    target->m_action = action;
  }
  QObject::connect(action, SIGNAL(actionFinished()), game,
                   SLOT(onActionFinish()));
  action->start();
}

bool UnitController::attackSettlement(Attack *attack) {
  if (attack->attackType() == Attack::Explosion) {
    // 爆炸是AOE
    auto unit = attack->m_unit;
    auto map = unit->m_game->m_pLevel->m_pMap;
    auto x = unit->LogicPos().x(), y = unit->LogicPos().y();
    for (int i = x - 1; i <= x + 1; i++) {
      for (int j = y - 1; j <= y + 1; j++) {
        // 不对自己进行操作，否则会把自己remove两次
        if (i == x && j == y) {
          continue;
        }
        if (!MapController::posLegal(QPoint(i, j))) {
          continue;
        }
        auto block = (*map)[i][j];
        if (block->occupation()) {
          auto &property = block->unit()->property();
          property.hp -= unit->property().attack;
          if (property.hp <= 0) {
            removeUnit(block->unit());
          }
        }
      }
    }
    removeUnit(unit);
    return false;
  } else if (attack->attackType() == Attack::Fireball) {
    // Fireball也是AOE，但略有不同
    auto unit = attack->m_target;
    auto map = unit->m_game->m_pLevel->m_pMap;
    auto x = unit->LogicPos().x(), y = unit->LogicPos().y();
    auto &source = attack->m_unit, &target = attack->m_target;
    auto attackment = source->property().attack >> 1;
    for (int i = x - 1; i <= x + 1; i++) {
      for (int j = y - 1; j <= y + 1; j++) {
        if (!MapController::posLegal(QPoint(i, j))) {
          continue;
        }
        auto block = (*map)[i][j];
        if (block->occupation()) {
          auto &property = block->unit()->property();
          property.hp -= attackment;
          if (property.hp <= 0) {
            removeUnit(block->unit());
            if (block->unit() == source) {
              source = nullptr;
            }
            if (block->unit() == target) {
              target = nullptr;
            }
          }
        }
      }
    }
    return false;
  } else if (attack->attackType() == Attack::Tap ||
             attack->attackType() == Attack::Strike) {
    // 分为两个Round，round1是我打你，round2是你打我
    Ability &propertyS = attack->m_unit->property();
    Ability &propertyT = attack->m_target->property();
    auto &source = attack->m_unit, &target = attack->m_target;
    if (attack->m_nRound == 1) {
      propertyT.hp -= propertyS.attack;
      if (propertyT.hp <= 0) {
        removeUnit(target);
        target = nullptr;
        return false;
      }
    } else {
      propertyS.hp -= propertyT.attack;
      if (propertyS.hp <= 0) {
        removeUnit(source);
        source = nullptr;
        return false;
      }
    }
    return true;
  }
  return true;
}

void UnitController::removeUnit(Unit *unit) {
  (*unit->m_game->m_pLevel->m_pMap)[unit->LogicPos()]->setOccupation(false);
  auto &units = unit->m_game->m_units;
  // 从全局vector里面移除
  for (auto it = units.begin(); it != units.end(); it++) {
    if (*it == unit) {
      units.erase(it);
      break;
    }
  }
  // 从场景中删除
  unit->scene()->removeItem(unit);
  unit->deleteLater();
}

void UnitController::closeGameUI(GameMain *game, GameUI *ui) {
  switch (ui->uiType()) {
  case GameUI::UnitMove: {
    auto unit = ((UnitMove *)ui)->m_unit;
    game->scene()->removeItem(ui);
    unit->m_unitMoveMenu = nullptr;
    unit->m_bUnitMoveMenu = false;
    game->m_pOverlayUI = nullptr;
    break;
  }
  case GameUI::UnitActionMenu: {
    auto unit = ((UnitActionMenu *)ui)->m_unit;
    game->scene()->removeItem(ui);
    unit->m_unitActionUI = nullptr;
    game->m_pOverlayUI = nullptr;
    game->m_bAction = false;
    break;
  }
  case GameUI::UnitAttack: {
    auto unit = ((UnitMove *)ui)->m_unit;
    game->scene()->removeItem(ui);
    unit->m_unitAttackMenu = nullptr;
    game->m_pOverlayUI = nullptr;
  }
  default: {
    break;
  }
  }
}

/**
 * @brief comp 按照y从小到大排序
 * @param u1
 * @param u2
 * @return
 */
bool comp(Unit *u1, Unit *u2) {
  return u1->LogicPos().y() < u2->LogicPos().y();
}

void UnitController::adjustZValue(GameMain *game) {
  auto &units = game->m_units;
  std::stable_sort(units.begin(), units.end(), comp);
  for (size_t i = 0; i < units.size(); i++) {
    units[i]->setZValue(300 + i); // unit的zvalue是300+
  }
}
