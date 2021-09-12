#ifndef GAMEITEM_H
#define GAMEITEM_H

#include "GameConfig.h"
#include "gamescene.h"

#include <QGraphicsItem>
#include <QObject>

/**
 * @brief 所有可以看见的对象的基类，包括Unit、Block、GameUI等等
 */
class GameItem : public QObject, public QGraphicsItem {
  Q_OBJECT
  Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
  GameItem(QGraphicsItem *parent = nullptr);

  virtual ~GameItem();

  /**
   * @brief setLogicPos 逻辑坐标系统，内部会设置item的实际坐标
   */
  virtual void setLogicPos(QPoint);

  QPoint LogicPos() const;

  /**
   * @brief scene
   * 继承来的scene()返回QGraphicsScene，会导致调用不了GameScene的一些属性，所以重写一下
   * @return GameScene*
   */
  GameScene *scene() const { return (GameScene *)QGraphicsItem::scene(); }

protected:
  /**
   * @brief paint 重载paint纯虚函数
   * @param painter
   * @param option
   * @param widget
   */
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) override;

  /**
   * @brief boundingRect 重载boundingRect纯虚函数
   * @return
   */
  virtual QRectF boundingRect() const override;

  /**
   * @brief image
   * 把上面两个纯虚函数用这一个纯虚函数代替，所有子类只需要实现这一个函数就可以完成绘图，进一步封装和简化API
   * @return
   */
  virtual const Image *image() const = 0;

  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

  virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

  /**
   * @brief onClick
   * 因为QGraphicsItem实现的点击事件很难用，所以统一包装为onClick虚函数
   * @param event
   */
  virtual void onClick(QGraphicsSceneMouseEvent *event);

protected slots:
  /**
   * @brief onFrameChange 播放gif的时候需要update()当前对象
   * @param frameNumber
   */
  void onFrameChange(int frameNumber);

protected:
  GameMain *m_game;
  friend void GameScene::addItem(GameItem *item);

private:
  QPoint m_logicPos;
  bool m_bClickValid;
};

#endif // GAMEITEM_H
