#include "unitcontroller.h"
#include "action.h"
#include "gamemain.h"
#include "gamemap.h"
#include "level.h"
#include "mapcontroller.h"
#include "unit.h"


#include <QHash>
#include <QHashIterator>
#include <QObject>
#include <QPair>
#include <queue>


void UnitController::PrepareAction(GameMain *game, Unit *unit, QPointF pos) {
  auto &menu = unit->m_unitActionUI;
  menu = new UnitActionMenu(unit);
  game->scene()->addItem(menu);
  menu->setPos(pos);
  //    QObject::connect(menu,SIGNAL(GameUIClosed(GameUI*)),game,SLOT(onGameUIClose(GameUI*)));
  game->m_bAction = true;
  game->m_pOverlayUI = menu;
}

void UnitController::PrepareMoveAction(GameMain *game, Unit *unit) {
  auto dests = MapController::SPFA(game, unit);
  auto &menu = unit->m_unitMoveMenu;
  menu = new UnitMove(unit, dests);
  menu->setPos(QPointF(0, 0));
  game->scene()->addItem(menu);
  unit->m_bUnitMoveMenu = true;
  //    QObject::connect(menu,SIGNAL(DestSelected(QPoint)),unit,SLOT(onDestSelect(QPoint)));
  //    QObject::connect(menu,SIGNAL(GameUIClosed(GameUI*)),game,SLOT(onGameUIClose(GameUI*)));
  game->m_pCurrentAction = new Move(unit, game);
  game->m_bAction = true;
  game->m_pOverlayUI = menu;
}

void UnitController::StartMoveAction(GameMain *game, Unit *unit, QPoint dest) {
  qDebug() << "start move action";
  auto route = MapController::FindRoute(game, unit, dest);
  Move *action = (Move *)(game->m_pCurrentAction);
  action->setTarget(dest);
  action->setRoute(route);
  QObject::connect(action, SIGNAL(actionFinished()), game,
                   SLOT(onActionFinish()));
  action->start();
}

void UnitController::PrepareAttackAction(GameMain *game, Unit *unit,
                                         Attack::AttackType type) {
  auto map = game->m_pLevel->m_pMap;
  std::vector<QPoint> range;
  std::vector<Unit *> targets;
  switch (type) {
  case Attack::Tap:
  case Attack::Strike: {
    auto pos = unit->LogicPos();
    for (int i = 0; i < 4; i++) {
      auto x = pos + MapController::sm_directions[i];
      if (!MapController::PosLegal(x)) {
        continue;
      }
      auto block = (*map)[x];
      if (MapController::Walkable(block->blockType(), unit->unitType())) {
        range.push_back(x);
        if (block->occupation()) {
          targets.push_back(block->unit());
        }
      }
    }
    break;
  }
  case Attack::Fireball: {
    break;
  }
  case Attack::Explosion: {
    break;
  }
  }
  auto menu = unit->m_unitAttackMenu;
  menu = new UnitAttack(unit, range, targets);
  menu->setPos(QPoint(0, 0));
  game->scene()->addItem(menu);
  game->m_pOverlayUI = menu;

  game->m_pCurrentAction = new Attack(unit, type, game);
  game->m_bAction = true;
}

void UnitController::StartAttackAction(GameMain *game, Unit *unit,
                                       Unit *target) {
  Attack *action = (Attack *)game->m_pCurrentAction;
  action->setTarget(target);
  QObject::connect(action, SIGNAL(actionFinished()), game,
                   SLOT(onActionFinish()));
  action->start();
}

void UnitController::FinishCurrentAction(GameMain *game) {
  if (game->m_pCurrentAction) {
    delete game->m_pCurrentAction;
    game->m_pCurrentAction = nullptr;
  }
  game->m_bAction = false;
}

void UnitController::CloseGameUI(GameMain *game, GameUI *ui) {
  qDebug() << "close gameui";
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
    //            unit->m_bUnitMoveMenu=false;
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
