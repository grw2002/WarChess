#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QObject>

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene(QObject *parent = nullptr);
    virtual ~GameScene();
};

#endif // GAMESCENE_H
