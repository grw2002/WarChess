#include "gameview.h"

GameView::GameView(QWidget *parent):
    QGraphicsView(parent)
{

}

GameView::~GameView(){}

void GameView::wheelEvent(QWheelEvent *event){
    Q_UNUSED(event);
}
