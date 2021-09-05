#ifndef UNIT_H
#define UNIT_H

#include "image.h"
#include "gameitem.h"
#include "imageinitializer.h"

#include <QObject>
#include <QDebug>
#include <QTransform>
#include <unordered_map>

class GameMain;

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

    virtual UnitType unitType() const = 0;

    virtual PlayerType playerType() const = 0;

    virtual void setDirect(Direct newDirect) {
        m_direct=newDirect;
        if(newDirect==Left) {
            setTransform(sm_transLeft);
        }
        if(newDirect==Right) {
            setTransform(sm_transRight);
        }
    }

    virtual Direct direct() const {
        return m_direct;
    }

    virtual Status status() const {
        return m_status;
    }

public:
    Direct m_direct;
    Status m_status;
    int m_hp, m_level;
    const static QTransform sm_transLeft, sm_transRight;
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

    static std::unordered_map<Status, Image*> sm_images;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override{
        Q_UNUSED(event);
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
    }

private:
    const Image* m_image;
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

    static std::unordered_map<Status, Image*> sm_images;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override{
        Q_UNUSED(event);
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
    }

private:
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

    static std::unordered_map<Status, Image*> sm_images;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override{
        Q_UNUSED(event);
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
    }

private:
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

    static std::unordered_map<Status, Image*> sm_images;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override{
        Q_UNUSED(event);
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
    }

private:
    const Image* m_image;
    const Image* image() const override;
    friend void ImageInitializer::ImageInitial();
};

#endif // UNIT_H
