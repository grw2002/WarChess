#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <QGraphicsItem>
#include <QObject>

class GameItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    GameItem(QGraphicsItem *parent = nullptr);
    virtual ~GameItem();
};

#endif // GAMEITEM_H
