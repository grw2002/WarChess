#include "mapcontroller.h"
#include "gamemain.h"
#include "gamemap.h"
#include "level.h"
#include "unit.h"

#include <cmath>
#include <queue>


/**
 * @brief PointToPair 点转换为QPair<int, int>
 * @param p
 * @return
 */
QPair<int, int> PointToPair(const QPoint p) {
  return QPair<int, int>(p.x(), p.y());
}

bool MapController::posLegal(QPoint pos) {
  if (pos.x() < 1 || pos.x() > NUMX || pos.y() < 1 || pos.y() > NUMY) {
    return false;
  }
  return true;
}

bool MapController::walkable(Block::BlockType blockType,
                             Unit::UnitType unitType) {
  switch (unitType) {
  // 玩家
  case Unit::Steve:
  case Unit::Golem:
  case Unit::Enderman: {
    switch (blockType) {
    case Block::Dirt:
    case Block::Grass:
    case Block::Stone:
    case Block::GrassPath:
    case Block::Ice: {
      return true;
      break;
    }
    default: {
      break;
    }
    }
    break;
  }
  // 敌方
  case Unit::Zombie:
  case Unit::Creeper:
  case Unit::Skeleton: {
    switch (blockType) {
    case Block::Dirt:
    case Block::Grass:
    case Block::Stone:
    case Block::GrassPath:
    case Block::Ice:
    case Block::NetherPortal: {
      return true;
      break;
    }
    default: {
      break;
    }
    }
    break;
  }
  // 村民
  case Unit::Villager: {
    switch (blockType) {
    case Block::GrassPath: {
      return true;
      break;
    }
    default: {
      break;
    }
    }
    break;
  }
  };
  return false;
}

void MapController::setOccupation(const GameMain *game, Unit *unit,
                                  QPoint logicpos, QPoint prevpos) {
  if (prevpos != QPoint(-1, -1)) { // (-1,-1)为缺省值
    auto block = (*(game->m_pLevel->m_pMap))[prevpos];
    block->m_bOccupied = false;
    block->m_unit = nullptr;
  }
  auto block = (*(game->m_pLevel->m_pMap))[logicpos];
  block->m_bOccupied = true;
  block->m_unit = unit;
  warMist(game);
}

const QPoint MapController::sm_directions[4] = {QPoint(1, 0), QPoint(-1, 0),
                                                QPoint(0, 1), QPoint(0, -1)};

std::vector<QPoint> MapController::spfa(const GameMain *game, const Unit *unit,
                                        int movable) {
  auto map = game->m_pLevel->m_pMap;
  std::vector<QPoint> res;
  std::queue<QPoint> q;
  QHash<QPair<int, int>, int> dis;
  QHash<QPair<int, int>, bool> vis;
  dis[PointToPair(unit->LogicPos())] = 0;
  q.push(unit->LogicPos());
  while (!q.empty()) {
    auto p = q.front();
    auto p_pair = PointToPair(p);
    q.pop();
    vis[p_pair] = false;
    // 剪枝加速
    if (dis[PointToPair(p)] >= movable) {
      continue;
    }
    for (int i = 0; i < 4; i++) {
      auto x = p + sm_directions[i];
      if (!posLegal(x)) {
        continue;
      }
      if ((*map)[x]->occupation()) {
        continue;
      }
      if (unit->unitType() == Unit::Villager &&
          (*map)[x]->blockType() != Block::GrassPath) {
        continue;
      }
      auto x_pair = PointToPair(x);
      if (walkable((*map)[x]->blockType(), unit->unitType())) {
        int dist = dis[p_pair] + ((*map)[x]->blockType() == Block::Ice ? 0 : 1);
        // 注意这里是严格小于，否则0权的时候会死循环
        if (!dis.contains(x_pair) || dist < dis[x_pair]) {
          dis[x_pair] = dist;
          // spfa精髓
          if (!vis.contains(x_pair) || !vis[x_pair]) {
            vis[x_pair] = true;
            q.push(x);
          }
        }
      }
    }
  }
  QHashIterator<QPair<int, int>, int> it(dis);
  while (it.hasNext()) {
    it.next();
    res.push_back(QPoint(it.key().first, it.key().second));
  }
  return res;
}

std::stack<QPoint> MapController::findRoute(const GameMain *game,
                                            const Unit *unit, QPoint dest,
                                            int movable) {
  std::stack<QPoint> res;
  auto map = game->m_pLevel->m_pMap;
  std::queue<QPoint> q;
  QHash<QPair<int, int>, int> dis;
  QHash<QPair<int, int>, bool> vis;
  QHash<QPair<int, int>, QPoint> prev;
  dis[PointToPair(unit->LogicPos())] = 0;
  q.push(unit->LogicPos());
  while (!q.empty()) {
    auto p = q.front();
    auto p_pair = PointToPair(p);
    q.pop();
    vis[p_pair] = false;
    // 剪枝加速
    if (dis[PointToPair(p)] >= movable) {
      continue;
    }
    for (int i = 0; i < 4; i++) {
      auto x = p + sm_directions[i];
      if (!posLegal(x)) {
        continue;
      }
      if ((*map)[x]->occupation()) {
        continue;
      }
      if (unit->unitType() == Unit::Villager &&
          (*map)[x]->blockType() != Block::GrassPath) {
        continue;
      }
      auto x_pair = PointToPair(x);
      if (walkable((*map)[x]->blockType(), unit->unitType())) {
        int dist = dis[p_pair] + ((*map)[x]->blockType() == Block::Ice ? 0 : 1);
        // 注意这里是严格小于，否则0权的时候会死循环
        if (!dis.contains(x_pair) || dist < dis[x_pair]) {
          dis[x_pair] = dist;
          prev[x_pair] = p;
          // spfa精髓
          if (!vis.contains(x_pair) || !vis[x_pair]) {
            vis[x_pair] = true;
            q.push(x);
          }
        }
      }
    }
  }
  auto cur = dest;
  res.push(cur);
  do {
    res.push(prev[PointToPair(cur)]);
    cur = prev[PointToPair(cur)];
  } while (cur != unit->LogicPos());
  return res;
}

void MapController::warMist(const GameMain *game) {
  if (game->m_pLevel->levelType() != Level::Assault) {
    return;
  }
  auto map = game->m_pLevel->m_pMap;
  for (int i = 1; i <= NUMX; i++) {
    for (int j = 1; j <= NUMY; j++) {
      (*map)[i][j]->m_bVisible = false;
    }
  }
  for (int i = 1; i <= NUMX; i++) {
    for (int j = 1; j <= NUMY; j++) {
      auto block = (*map)[i][j];
      if (!block->occupation()) {
        continue;
      }
      auto unit = block->unit();
      if (unit->playerType() == Unit::Player) {
        // 这里应当用探测力detection作为迷雾范围
        int detection = unit->property().detection;
        for (int k = i - detection; k <= i + detection; k++) {
          for (int l = j - detection; l <= j + detection; l++) {
            if (posLegal(QPoint(k, l)) &&
                euclidDistance(QPoint(k, l), QPoint(i, j)) <= detection) {
              (*map)[k][l]->m_bVisible = true;
            }
          }
        }
      }
    }
  }
  game->scene()->update();
}

double MapController::euclidDistance(QPoint p1, QPoint p2) {
  return sqrt((p1.x() - p2.x()) * (p1.x() - p2.x()) +
              (p1.y() - p2.y()) * (p1.y() - p2.y()));
}

bool MapController::blockVisible(GameMain *game, QPoint pos) {
  return (*game->m_pLevel->m_pMap)[pos]->m_bVisible;
}
