#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "GameConfig.h"
#include "gamemain.h"

class GameController {
public:
  /**
   * @brief nextRound 下一轮（不切换side）
   * @param game
   */
  static void nextRound(GameMain *game);
  /**
   * @brief nextRound 下一轮（切换敌我side）
   * @param game
   */
  static void nextRound(GameMain *game, GameMain::GameStatus);
  /**
   * @brief FinishCurrentAction 结束当前活动的Action
   * @param game
   */
  static void finishCurrentAction(GameMain *game);
};

#endif // GAMECONTROLLER_H
