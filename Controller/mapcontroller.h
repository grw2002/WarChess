#ifndef MAPCONTROLLER_H
#define MAPCONTROLLER_H

#include "GameConfig.h"
#include "gamemap.h"
#include "unit.h"

#include <QPoint>
#include <stack>
#include <vector>

class MapController {
public:
  /**
   * @brief setOccupation 当前位置占用情况
   * @param game
   * @param unit
   * @param logicpos
   * @param prevpos
   */
  static void setOccupation(const GameMain *game, Unit *unit, QPoint logicpos,
                            QPoint prevpos = QPoint(-1, -1));
  /**
   * @brief spfa 寻找可以移动的范围
   * @param game
   * @param unit
   * @param movable
   * @return
   */
  static std::vector<QPoint> spfa(const GameMain *game, const Unit *unit,
                                  int movable);
  /**
   * @brief findRoute 寻找到目标点的路径
   * @param game
   * @param unit
   * @param dest
   * @param movable
   * @return
   */
  static std::stack<QPoint> findRoute(const GameMain *game, const Unit *unit,
                                      QPoint dest, int movable = INF);
  /**
   * @brief warMist 重新计算战争迷雾
   * @param game
   */
  static void warMist(const GameMain *game);
  /**
   * @brief blockVisible 当前个点是否在迷雾里
   * @param game
   * @param pos
   * @return
   */
  static bool blockVisible(GameMain *game, QPoint pos);
  /**
   * @brief posLevel 当前位置是否合法
   * @param pos
   * @return
   */
  static bool posLegal(QPoint pos);
  /**
   * @brief walkAble 当前位置玩家是否能通行
   * @param blockType
   * @param unitType
   * @return
   */
  static bool walkable(Block::BlockType blockType, Unit::UnitType unitType);
  /**
   * @brief euclidDistance 欧几里得距离
   * @param p1
   * @param p2
   * @return
   */
  static double euclidDistance(QPoint p1, QPoint p2);
  /**
   * @brief sm_directions 上下左右四个方向
   */
  static const QPoint sm_directions[4];
};

#endif // MAPCONTROLLER_H
