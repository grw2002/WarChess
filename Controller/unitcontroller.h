#ifndef UNITCONTROLLER_H
#define UNITCONTROLLER_H

#include "GameConfig.h"
#include "action.h"
#include <stack>
#include <vector>

class UnitController {
public:
  /**
   * @brief prepareAction 玩家准备Action（弹出选择菜单）
   * @param game
   * @param unit
   * @param pos
   */
  static void prepareAction(GameMain *game, Unit *unit, QPointF pos);
  /**
   * @brief prepareMoveAction 准备玩家Move Action，显示可达范围
   * @param game
   * @param unit
   */
  static void prepareMoveAction(GameMain *game, Unit *unit);
  /**
   * @brief prepareEnemyMoveAction 敌方AI，准备敌方Move Action
   * @param game
   * @param unit
   */
  static void prepareEnemyMoveAction(GameMain *game, Unit *unit);
  /**
   * @brief startMoveAction 开始当前单位的Move
   * @param game
   * @param unit
   * @param dest
   */
  static void startMoveAction(GameMain *game, Unit *unit, QPoint dest);
  /**
   * @brief prepareAttackAction 准备Attack Action，显示攻击范围
   * @param game
   * @param unit
   * @param type
   */
  static void prepareAttackAction(GameMain *game, Unit *unit,
                                  Attack::AttackType type);
  /**
   * @brief prepareEnemyAttackAction 敌方AI，准备敌方Attack Action
   * @param game
   * @param unit
   */
  static void prepareEnemyAttackAction(GameMain *game, Unit *unit);
  /**
   * @brief startAttackAction   开始当前单位Attack Action
   * @param game
   * @param unit
   * @param target
   */
  static void startAttackAction(GameMain *game, Unit *unit, Unit *target);
  /**
   * @brief attackSettlement 上海结算
   * @param attack
   * @return
   */
  static bool attackSettlement(Attack *attack);
  /**
   * @brief closeGameUI 关闭当前UI
   * @param game
   * @param ui
   */
  static void closeGameUI(GameMain *game, GameUI *ui);
  /**
   * @brief adjustZValue 处理遮挡问题
   * @param game
   */
  static void adjustZValue(GameMain *game);

private:
  static void removeUnit(Unit *unit);
};

#endif // UNITCONTROLLER_H
