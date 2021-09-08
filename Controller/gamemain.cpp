#include "gamemain.h"
#include "imageinitializer.h"
#include "gameui.h"
#include "action.h"
#include "gamescene.h"
#include "level.h"
#include "unit.h"
#include "gameview.h"
#include "unitcontroller.h"

GameMain::GameMain(GameView *gameview, QObject *parent) :
    QObject(parent),
    m_status(Self),
    m_bAction(false),
    m_pCurrentAction(nullptr)
{
    ImageInitializer::ImageInitial();
    m_scene=new GameScene(this, gameview);
    m_scene->addRect(0,0,MAP_WIDTH,MAP_HEIGHT);

    m_pLevel=new Level(m_scene,this);

    Unit *s1=new Steve();
    s1->setLogicPos(QPoint(28,20));
    m_units.push_back(s1);
    m_scene->addItem(s1);

//    GameUI *ui1=new UnitStatus(s1);
//    ui1->setLogicPos(QPoint((NUMX>>1)+1,NUMY>>1));
//    m_scene->addItem(ui1);

//    Unit *s2=new Golem();
//    s2->setLogicPos(QPoint((NUMX>>1)+1,NUMY>>1));
//    m_units.push_back(s2);
//    m_scene->addItem(s2);

//    Unit *s3=new Zombie();
//    s3->setLogicPos(QPoint(NUMX>>1,(NUMY>>1)+1));
//    m_units.push_back(s3);
//    m_scene->addItem(s3);

//    Unit *s4=new Creeper();
//    s4->setLogicPos(QPoint((NUMX>>1)+1,(NUMY>>1)+1));
//    m_units.push_back(s4);
//    m_scene->addItem(s4);

//    Bullet *b1=new Explosion();
//    b1->setLogicPos(QPoint(10,10));
//    m_scene->addItem(b1);
}

GameScene* GameMain::scene() const
{
    return m_scene;
}

void GameMain::onActionFinish() {
    UnitController::FinishCurrentAction(this);
}
