#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <vector>

class GameMap;
class GameScene;
class Unit;

class Level : public QObject {
  Q_OBJECT
public:
  explicit Level(GameScene *scene, QObject *parent = nullptr);

  virtual ~Level();

signals:

public:
  GameMap *m_pMap;
  //    std::vector<Unit*> m_units;
};

#endif // LEVEL_H
