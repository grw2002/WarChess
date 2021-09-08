#ifndef UNIT_H
#define UNIT_H

#include "GameConfig.h"
#include "imageinitializer.h"
#include "gameitem.h"
#include "gameui.h"

#include <QObject>
#include <QDebug>
#include <QTransform>
#include <unordered_map>
#include <QGraphicsSceneHoverEvent>

class GameMain;
class UnitController;
class Move;

struct Ability {
    int hp;
    int movable;
    int attack;
};

class Unit : public GameItem
{
    Q_OBJECT
public:
    enum UnitType {
        Zombie=1,
        Creeper=2,
        Skeleton=3,
        Steve=11,
        Golem=12,
        Enderman=13,
        Villager=14,
    };

    enum PlayerType {
        Player=1,
        Enemy=2
    };

    enum Direct {
        Up=1,
        Down=2,
        Left=3,
        Right=4
    };

    enum Status {
        Hold=1,
        Walk=2,
        Attack=3
    };

    explicit Unit(QGraphicsItem *parent = nullptr);

    virtual ~Unit();

    virtual UnitType unitType() const = 0;

    virtual PlayerType playerType() const = 0;

    virtual void setDirect(Direct newDirect);

    virtual Direct direct() const {
        return m_direct;
    }

    virtual Status status() const {
        return m_status;
    }

    virtual Ability ability() const = 0;

public slots:
    void onDestSelect(QPoint dest);

protected:
    virtual void onClick(QGraphicsSceneMouseEvent *event) override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;

    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

protected:
    Status m_status;
    Direct m_direct;


private:
    GameUI *m_itemUI;
    bool m_facingRight;
    const static QTransform sm_transLeft, sm_transRight;
    bool m_bUnitMoveMenu;
    GameUI *m_unitMoveMenu;
    friend class UnitController;
    friend class Move;
    friend void UnitStatus::onClick(QGraphicsSceneMouseEvent *event);
};

// Steve

class Steve: public Unit
{
    Q_OBJECT
public:
    explicit Steve(QGraphicsItem *parent = nullptr);

    ~Steve();

    UnitType unitType() const override;

    PlayerType playerType() const override;

    Ability ability() const override {
        return m_ability;
    }

private:
    static std::unordered_map<Status, Image*> sm_images;
    const Image* m_image;
    Ability m_ability;
    const Image* image() const override;
    friend void ImageInitializer::ImageInitial();
};

// Golem

class Golem: public Unit
{
    Q_OBJECT
public:
    explicit Golem(QGraphicsItem *parent = nullptr);

    ~Golem();

    UnitType unitType() const override;

    PlayerType playerType() const override;

protected:
    virtual void onClick(QGraphicsSceneMouseEvent *event) override {
        switch (m_status) {
        case Hold:
            m_status=Walk;
            break;
        case Walk:
            m_status=Attack;
            break;
        case Attack:
            m_status=Hold;
            break;
        }
        m_image=sm_images[m_status];
        Unit::onClick(event);
    }

private:
    static std::unordered_map<Status, Image*> sm_images;
    const Image* m_image;
    const Image* image() const override;
    friend void ImageInitializer::ImageInitial();
};

// Zombie

class Zombie: public Unit
{
    Q_OBJECT
public:
    explicit Zombie(QGraphicsItem *parent = nullptr);

    ~Zombie();

    UnitType unitType() const override;

    PlayerType playerType() const override;

protected:
    virtual void onClick(QGraphicsSceneMouseEvent *event) override {
        switch (m_status) {
        case Hold:
            m_status=Walk;
            break;
        case Walk:
            m_status=Attack;
            break;
        case Attack:
            m_status=Hold;
            break;
        }
        m_image=sm_images[m_status];
        Unit::onClick(event);
    }

private:
    static std::unordered_map<Status, Image*> sm_images;
    const Image* m_image;
    const Image* image() const override;
    friend void ImageInitializer::ImageInitial();
};

// Creeper

class Creeper: public Unit
{
    Q_OBJECT
public:
    explicit Creeper(QGraphicsItem *parent = nullptr);

    ~Creeper();

    UnitType unitType() const override;

    PlayerType playerType() const override;

protected:
    virtual void onClick(QGraphicsSceneMouseEvent *event) override {
        switch (m_status) {
        case Hold:
            m_status=Walk;
            break;
        case Walk:
            m_status=Attack;
            break;
        case Attack:
            m_status=Hold;
            break;
        }
        m_image=sm_images[m_status];
        Unit::onClick(event);
    }

private:
    static std::unordered_map<Status, Image*> sm_images;
    const Image* m_image;
    const Image* image() const override;
    friend void ImageInitializer::ImageInitial();
};

#endif // UNIT_H
