#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "GameConfig.h"

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QEvent>

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene(GameMain *game, QObject *parent = nullptr);
    virtual ~GameScene();
    void addItem(GameItem *item);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
        m_pressPos=mouseEvent->screenPos();
//        QGraphicsScene::mousePressEvent(mouseEvent);
    }

//    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
//        qDebug()<<"scene move";
//    }

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
        if(m_pressPos==mouseEvent->screenPos()) {
            QGraphicsScene::mousePressEvent(mouseEvent);
        }
//        QGraphicsScene::mouseReleaseEvent(mouseEvent);
    }

private:
    GameMain *m_game;
    QPointF m_pressPos;
};

#endif // GAMESCENE_H
