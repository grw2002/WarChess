#include "mapcontroller.h"
#include "gamemain.h"
#include "gamemap.h"
#include "level.h"
#include "unit.h"

#include <queue>

QPair<int, int> PointToPair(const QPoint p) {
  return QPair<int, int>(p.x(), p.y());
}

bool MapController::PosLegal(QPoint pos) {
  if (pos.x() < 1 || pos.x() > NUMX || pos.y() < 1 || pos.y() > NUMY) {
    return false;
  }
  return true;
}

bool MapController::Walkable(Block::BlockType blockType,
                             Unit::UnitType unitType) {
  switch (unitType) {
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
  if (prevpos != QPoint(-1, -1)) {
    auto block = (*(game->m_pLevel->m_pMap))[prevpos];
    block->m_bOccupied = false;
    block->m_unit = nullptr;
  }
  auto block = (*(game->m_pLevel->m_pMap))[logicpos];
  block->m_bOccupied = true;
  block->m_unit = unit;
}

const QPoint MapController::sm_directions[4] = {QPoint(1, 0), QPoint(-1, 0),
                                                QPoint(0, 1), QPoint(0, -1)};

std::vector<QPoint> MapController::SPFA(const GameMain *game,
                                        const Unit *unit) {
  qDebug() << "hello BFS!" << game << (QObject *)unit;
  auto map = game->m_pLevel->m_pMap;
  int movable = unit->ability().movable;
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
    if (dis[PointToPair(p)] >= movable) {
      continue;
    }
    for (int i = 0; i < 4; i++) {
      auto x = p + sm_directions[i];
      if (!PosLegal(x)) {
        continue;
      }
      if ((*map)[x]->occupation()) {
        continue;
      }
      auto x_pair = PointToPair(x);
      if (Walkable((*map)[x]->blockType(), unit->unitType())) {
        if (!dis.contains(x_pair) || dis[p_pair] + 1 < dis[x_pair]) {
          dis[x_pair] = dis[p_pair] + 1;
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

std::stack<QPoint> MapController::FindRoute(const GameMain *game,
                                            const Unit *unit, QPoint dest) {
  qDebug() << "hey DFS!" << game << (QObject *)unit;
  std::stack<QPoint> res;
  auto map = game->m_pLevel->m_pMap;
  int movable = unit->ability().movable;
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
    if (dis[PointToPair(p)] >= movable) {
      continue;
    }
    for (int i = 0; i < 4; i++) {
      auto x = p + sm_directions[i];
      if (!PosLegal(x)) {
        continue;
      }
      if ((*map)[x]->occupation()) {
        continue;
      }
      auto x_pair = PointToPair(x);
      if (Walkable((*map)[x]->blockType(), unit->unitType())) {
        if (!dis.contains(x_pair) || dis[p_pair] + 1 < dis[x_pair]) {
          dis[x_pair] = dis[p_pair] + 1;
          prev[x_pair] = p;
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
