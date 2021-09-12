#include "gamecontroller.h"
#include "gamemain.h"
#include "gamemap.h"
#include "level.h"
#include "unit.h"
#include "unitcontroller.h"


#include <QStyle>
#include <cstdlib>
#include <ctime>


void GameController::nextRound(GameMain *game) {
  // 是否可以决出胜负
  if (game->m_pLevel->VictoryJudge()) {
    return;
  }
  // 下一轮
  if (game->m_status == GameMain::Self) {
    return;
  } else if (game->m_status == GameMain::Enemy) {
    for (auto &unit : game->m_units) {
      if (unit->playerType() != Unit::Enemy) {
        continue;
      }
      if (!unit->moved()) {
        UnitController::prepareEnemyMoveAction(game, unit);
        return;
      } else if (!unit->attacked()) {
        UnitController::prepareEnemyAttackAction(game, unit);
        return;
      }
    }
    nextRound(game, GameMain::Self);
  }
}

void GameController::nextRound(GameMain *game, GameMain::GameStatus status) {
  // 是否可以决出胜负
  if (game->m_pLevel->NextStage(game, game->m_status, status)) {
    return;
  }
  // 更换side然后进入下一轮
  game->m_status = status;
  if (status == GameMain::Self) {
    game->m_sidebarSide->setText("当前轮次：我方");
    game->m_sidebarSide->setStyleSheet("color:green");
  } else if (status == GameMain::Enemy) {
    game->m_sidebarSide->setText("当前轮次：敌方");
    game->m_sidebarSide->setStyleSheet("color:red");
  }
  for (auto &unit : game->m_units) {
    unit->resetRoundState();
  }
  GameController::nextRound(game);
}

void GameController::finishCurrentAction(GameMain *game) {
  auto &action = game->m_pCurrentAction; //这里需要取引用
  if (action) {
    switch (action->actionType()) {
    // Action为移动
    case Action::Move: {
      Move *move = (Move *)action;
      if (move->status() == Action::End) {
        move->m_unit->m_bMoved = true;
      }
      move->m_unit->m_action = nullptr;
      break;
    }
    // Action为攻击
    case Action::Attack: {
      Attack *attack = (Attack *)action;
      if (attack->status() == Action::End && attack->m_unit) {
        attack->m_unit->m_bAttacked = true;
      }
      if (attack->m_unit) {
        attack->m_unit->m_action = nullptr;
      }
      if (attack->m_target) {
        attack->m_target->m_action = nullptr;
      }
      break;
    }
    };
    action->deleteLater();
    action = nullptr;
  }
  game->m_bAction = false;
  if (game->status() == GameMain::Enemy) {
    GameController::nextRound(game);
  }
}
