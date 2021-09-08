#ifndef GAMEUI_H
#define GAMEUI_H

#include "imageinitializer.h"
#include "gameitem.h"

#include <QObject>
#include <vector>

class Unit;

class GameUI : public GameItem
{
    Q_OBJECT
public:
    enum UIType {
        UnitStatus=1,
        GameInfo=2,
        UnitMove=3
    };

    GameUI(QGraphicsItem *parent = nullptr);

    virtual ~GameUI();

    virtual UIType uiType() const = 0;
};

class GameInfo: public GameUI {
public:
    GameInfo(QGraphicsItem *parent = nullptr);

    ~GameInfo();

    UIType uiType() const override {
        return GameUI::UnitStatus;
    }

protected:
    ;
};

class UnitStatus: public GameUI {
    Q_OBJECT
public:
    UnitStatus(Unit *unit, QGraphicsItem *parent = nullptr);

    ~UnitStatus();

    UIType uiType() const override {
        return GameUI::UnitStatus;
    }

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    virtual QRectF boundingRect() const override;

    virtual void onClick(QGraphicsSceneMouseEvent *event) override;

private:
    Unit *m_unit;
    QGraphicsTextItem *m_infoBox;
    const Image* image() const override;
    static const Image *m_book;
    friend void ImageInitializer::ImageInitial();
    const char* unitType() const;
    friend class Unit;
};

class UnitMove: public GameUI {
    Q_OBJECT
public:
    explicit UnitMove(Unit *unit, std::vector<QPoint> dests,QGraphicsItem *parent = nullptr);

    ~UnitMove();

    UIType uiType() const override {
        return GameUI::UnitMove;
    }

signals:
    void DestSelected(QPoint target);

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    virtual QRectF boundingRect() const override {
        return QRectF(0,0,2048,1536);
    }

    const Image* image() const override {
        return nullptr;
    }

    virtual void onClick(QGraphicsSceneMouseEvent *event) override;

private:
    Unit *m_unit;
    std::vector<QPoint> m_dests;
};

#endif // GAMEUI_H
