#ifndef GAMEMAIN_H
#define GAMEMAIN_H

#include <QObject>
#include <vector>

//#include "GameConfig.h"

#include "level.h"
#include "unit.h"
#include "action.h"
#include "uielement.h"

enum GameStatus {
    Start=0,
    End=1,
    Self=2,
    Enemy=3,
    Friend=4
};

class GameMain : public QObject
{
    Q_OBJECT
public:
    explicit GameMain(GameView *gameview=nullptr, QObject *parent = nullptr);
    GameScene* scene()const;

signals:

private:
    Level *m_pLevel;
    std::vector<Unit*> m_units;
    std::vector<UIElement> m_uiElements;
    GameStatus m_status;
    bool m_bAction;
    Action *m_pCurrentAction;
    GameScene *m_scene;
};


#endif // GAMEMAIN_H
