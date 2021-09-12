#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QWidget>

class GameView : public QGraphicsView {
  Q_OBJECT
public:
  GameView(QWidget *parent = nullptr);

  virtual ~GameView();

protected:
  /**
   * @brief wheelEvent 禁用鼠标滚轮
   * @param event
   */
  virtual void wheelEvent(QWheelEvent *event) override;
};

#endif // GAMEVIEW_H
