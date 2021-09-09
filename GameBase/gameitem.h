#ifndef GAMEITEM_H
#define GAMEITEM_H

#include "GameConfig.h"
#include "gamescene.h"
//#include "image.h"

#include <QGraphicsItem>
#include <QObject>

class GameMain;

class GameItem : public QObject, public QGraphicsItem {
  Q_OBJECT
  Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
  GameItem(QGraphicsItem *parent = nullptr);

  virtual ~GameItem();

  virtual void setLogicPos(QPoint);

  QPoint LogicPos() const;

  GameScene *scene() const { return (GameScene *)QGraphicsItem::scene(); }

protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) override;

  virtual QRectF boundingRect() const override;

  virtual const Image *image() const = 0;

  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
    qDebug() << "press";
    m_bClickValid = true;
    QGraphicsItem::mousePressEvent(event);
  }

  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override {
    qDebug() << "move";
    m_bClickValid = false;
    QGraphicsItem::mouseMoveEvent(event);
  }

  virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
    //        qDebug()<<"release"<<this->image();
    //        if(m_bClickValid) {
    onClick(event);
    //        }
    QGraphicsItem::mouseReleaseEvent(event);
  }

  virtual void onClick(QGraphicsSceneMouseEvent *event);

protected slots:
  void onFrameChange(int frameNumber);

protected:
  GameMain *m_game;
  friend void GameScene::addItem(GameItem *item);

private:
  QPoint m_logicPos;
  bool m_bClickValid;
};

#endif // GAMEITEM_H
