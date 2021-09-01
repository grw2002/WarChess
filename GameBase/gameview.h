#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QWidget>

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    GameView(QWidget *parent = nullptr);
    virtual ~GameView();
protected:
    virtual void wheelEvent(QWheelEvent *event) override;
};

#endif // GAMEVIEW_H
