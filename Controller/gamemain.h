#ifndef GAMEMAIN_H
#define GAMEMAIN_H

#include "GameConfig.h"

#include <QObject>
#include <vector>

class UnitController;

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

public slots:
    void onActionFinish();

signals:

private:
    Level *m_pLevel;
    std::vector<Unit*> m_units;
//    std::vector<UIElement> m_uiElements;
    GameStatus m_status;
    bool m_bAction;
    Action *m_pCurrentAction;
    GameScene *m_scene;

    friend class UnitController;
};


#endif // GAMEMAIN_H
