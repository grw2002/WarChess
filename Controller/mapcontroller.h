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
  static void setOccupation(const GameMain *game, Unit *unit, QPoint logicpos,
                            QPoint prevpos = QPoint(-1, -1));
  static std::vector<QPoint> SPFA(const GameMain *game, const Unit *unit);
  static std::stack<QPoint> FindRoute(const GameMain *game, const Unit *unit,
                                      QPoint dest);
  static const QPoint sm_directions[4];
  static bool PosLegal(QPoint pos);
  static bool Walkable(Block::BlockType blockType, Unit::UnitType unitType);
};

#endif // MAPCONTROLLER_H
