#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "GameConfig.h"

#include <QGraphicsScene>
#include <QObject>

/**
 * @brief 继承的游戏场景
 */
class GameScene : public QGraphicsScene {
  Q_OBJECT
public:
  GameScene(GameMain *game, QObject *parent = nullptr);

  virtual ~GameScene();

  /**
   * @brief addItem 重写addItem函数，注入m_game参数
   * @param item
   */
  void addItem(GameItem *item);

  // 下面两个函数配合GameItem实现了友好的点击事件

  virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

  virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
  GameMain *m_game;
  QPointF m_pressPos;
};

#endif // GAMESCENE_H
