#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <vector>

#include "gamemap.h"
#include "unit.h"

class Level : public QObject
{
    Q_OBJECT
public:
    explicit Level(QGraphicsScene *scene, QObject *parent = nullptr);

signals:

public:
    GameMap *m_pMap;
    std::vector<Unit*> m_units;
};

#endif // LEVEL_H
