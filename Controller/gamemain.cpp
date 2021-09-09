#include "gamemain.h"
#include "action.h"
#include "gamescene.h"
#include "gameui.h"
#include "gameview.h"
#include "imageinitializer.h"
#include "level.h"
#include "unit.h"
#include "unitcontroller.h"

GameMain::GameMain(GameView *gameview, QObject *parent)
    : QObject(parent), m_pOverlayUI(nullptr), m_status(Self), m_bAction(false),
      m_pCurrentAction(nullptr) {
  ImageInitializer::ImageInitial();
  m_scene = new GameScene(this, gameview);
  m_scene->addRect(0, 0, MAP_WIDTH, MAP_HEIGHT);

  m_pLevel = new Level(m_scene, this);

  Unit *s1 = new Steve();
  m_scene->addItem(s1);
  s1->setLogicPos(QPoint(28, 20));
  m_units.push_back(s1);

  //    GameUI *ui1=new UnitStatus(s1);
  //    ui1->setLogicPos(QPoint((NUMX>>1)+1,NUMY>>1));
  //    m_scene->addItem(ui1);

  Unit *s2 = new Golem();
  m_scene->addItem(s2);
  s2->setLogicPos(QPoint((NUMX >> 1) + 1, NUMY >> 1));
  m_units.push_back(s2);

  Unit *s3 = new Zombie();
  m_scene->addItem(s3);
  s3->setLogicPos(QPoint(27, 19));
  m_units.push_back(s3);

  Unit *s4 = new Creeper();
  m_scene->addItem(s4);
  s4->setLogicPos(QPoint((NUMX >> 1) + 1, (NUMY >> 1) + 1));
  m_units.push_back(s4);

  //    Bullet *b1=new Explosion();
  //    b1->setLogicPos(QPoint(10,10));
  //    m_scene->addItem(b1);
}

GameScene *GameMain::scene() const { return m_scene; }

void GameMain::onActionFinish() { UnitController::FinishCurrentAction(this); }

void GameMain::onGameUIClose(GameUI *gameui) {
  UnitController::CloseGameUI(this, gameui);
}

bool GameMain::Actioning() const { return m_bAction; }
