#include "unitcontroller.h"
#include "gamemain.h"
#include "unit.h"
#include "level.h"
#include "gamemap.h"
#include "action.h"

#include <queue>
#include <QPair>
#include <QHash>
#include <QHashIterator>
#include <QObject>

UnitController::UnitController()
{

}

QPair<int, int> PointToPair(const QPoint p) {
    return QPair<int, int>(p.x(),p.y());
}

std::vector<QPoint> UnitController::SPFA(GameMain *game, Unit *unit)
{
    qDebug()<<"hello BFS!"<<game<<(QObject*)unit;
    auto map=game->m_pLevel->m_pMap;
    int movable=unit->ability().movable;
    std::vector<QPoint> res;
    std::queue<QPoint> q;
    QHash<QPair<int, int>, int> dis;
    QHash<QPair<int, int>, bool> vis;
    QPoint direction[4]={QPoint(1,0),QPoint(-1,0),QPoint(0,1),QPoint(0,-1)};
    dis[PointToPair(unit->LogicPos())]=0;
    q.push(unit->LogicPos());
    while(!q.empty()) {
        auto p=q.front();
        auto p_pair=PointToPair(p);
        q.pop();
        vis[p_pair]=false;
        if(dis[PointToPair(p)]>=movable) {
//            qDebug()<<"continue"<<p;
            continue;
        }
        for(int i=0;i<4;i++) {
            auto x=p+direction[i];
            auto x_pair=PointToPair(x);
            switch ((*map)[x]->blockType()) {
                case Block::Dirt:
                case Block::Grass:
                case Block::Stone:
                case Block::GrassPath:
                case Block::Ice:
                {
                    if(!dis.contains(x_pair) || dis[p_pair]+1 < dis[x_pair]) {
                        dis[x_pair]=dis[p_pair]+1;
                        if(!vis.contains(x_pair) || !vis[x_pair]) {
                            vis[x_pair]=true;
                            q.push(x);
                        }
                    }
                }
            }
        }
    }
    QHashIterator<QPair<int, int>, int> it(dis);
    while(it.hasNext()) {
        it.next();
//        qDebug()<<it.key();
        res.push_back(QPoint(it.key().first,it.key().second));
    }
    return res;
}

void UnitController::StartMoveAction(GameMain *game, Unit *unit, QPoint dest) {
    qDebug()<<"start move action";
    auto route=FindRoute(game, unit, dest);
    Action *action=new Move(unit, dest, route);
    game->m_pCurrentAction=action;
    game->m_bAction=true;
    QObject::connect(action,SIGNAL(actionFinished()),game,SLOT(onActionFinish()));
}

std::stack<QPoint> UnitController::FindRoute(GameMain *game, Unit *unit, QPoint dest) {
    qDebug()<<"hey DFS!"<<game<<(QObject*)unit;
    std::stack<QPoint> res;
    auto map=game->m_pLevel->m_pMap;
    int movable=unit->ability().movable;
    std::queue<QPoint> q;
    QHash<QPair<int, int>, int> dis;
    QHash<QPair<int, int>, bool> vis;
    QHash<QPair<int, int>, QPoint> prev;
    QPoint direction[4]={QPoint(1,0),QPoint(-1,0),QPoint(0,1),QPoint(0,-1)};
    dis[PointToPair(unit->LogicPos())]=0;
    q.push(unit->LogicPos());
    while(!q.empty()) {
        auto p=q.front();
        auto p_pair=PointToPair(p);
        q.pop();
        vis[p_pair]=false;
        if(dis[PointToPair(p)]>=movable) {
//            qDebug()<<"continue"<<p;
            continue;
        }
        for(int i=0;i<4;i++) {
            auto x=p+direction[i];
            auto x_pair=PointToPair(x);
            switch ((*map)[x]->blockType()) {
                case Block::Dirt:
                case Block::Grass:
                case Block::Stone:
                case Block::GrassPath:
                case Block::Ice:
                {
                    if(!dis.contains(x_pair) || dis[p_pair]+1 < dis[x_pair]) {
                        dis[x_pair]=dis[p_pair]+1;
                        prev[x_pair]=p;
                        if(!vis.contains(x_pair) || !vis[x_pair]) {
                            vis[x_pair]=true;
                            q.push(x);
                        }
                    }
                }
            }
        }
    }
    auto cur=dest;
    res.push(cur);
    do {
//        qDebug()<<cur.x()<<cur.y();
        res.push(prev[PointToPair(cur)]);
        cur=prev[PointToPair(cur)];
    } while(cur != unit->LogicPos());
    return res;
}

void UnitController::FinishCurrentAction(GameMain* game) {
    delete game->m_pCurrentAction;
    game->m_pCurrentAction=nullptr;
    game->m_bAction=false;
}
