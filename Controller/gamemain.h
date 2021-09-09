#ifndef GAMEMAIN_H
#define GAMEMAIN_H

#include "GameConfig.h"
#include "gameitem.h"

#include <QObject>
#include <vector>

class UnitController;

enum GameStatus { Start = 0, End = 1, Self = 2, Enemy = 3, Friend = 4 };

class GameMain : public QObject {
  Q_OBJECT
public:
  explicit GameMain(GameView *gameview = nullptr, QObject *parent = nullptr);
  GameScene *scene() const;
  bool Actioning() const;

public slots:
  void onActionFinish();
  void onGameUIClose(GameUI *gameui);

public:
  GameUI *m_pOverlayUI;

signals:

private:
  Level *m_pLevel;
  std::vector<Unit *> m_units;
  GameStatus m_status;
  bool m_bAction;
  Action *m_pCurrentAction;
  GameScene *m_scene;

  friend class UnitController;
  friend class MapController;
};

#endif // GAMEMAIN_H
