#ifndef UNITCONTROLLER_H
#define UNITCONTROLLER_H

#include "GameConfig.h"
#include "action.h"
#include <stack>
#include <vector>


class UnitController {
public:
  //    static std::vector<QPoint> SPFA(GameMain *game, Unit *unit);
  static void PrepareAction(GameMain *game, Unit *unit, QPointF pos);
  static void PrepareMoveAction(GameMain *game, Unit *unit);
  static void StartMoveAction(GameMain *game, Unit *unit, QPoint dest);
  static void PrepareAttackAction(GameMain *game, Unit *unit,
                                  Attack::AttackType type);
  static void StartAttackAction(GameMain *game, Unit *unit, Unit *target);
  static void FinishCurrentAction(GameMain *game);
  static void CloseGameUI(GameMain *game, GameUI *ui);

private:
  //    static std::stack<QPoint> FindRoute(GameMain *game, Unit *unit, QPoint
  //    dest);
};

#endif // UNITCONTROLLER_H
