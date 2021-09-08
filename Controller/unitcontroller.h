#ifndef UNITCONTROLLER_H
#define UNITCONTROLLER_H

#include "GameConfig.h"
#include <vector>
#include <stack>

class UnitController
{
public:
    UnitController();

    static std::vector<QPoint> SPFA(GameMain *game, Unit *unit);
    static void StartMoveAction(GameMain *game, Unit *unit, QPoint dest);
    static void FinishCurrentAction(GameMain* game);

private:
    static std::stack<QPoint> FindRoute(GameMain *game, Unit *unit, QPoint dest);
};

#endif // UNITCONTROLLER_H
