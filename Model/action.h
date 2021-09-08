#ifndef ACTION_H
#define ACTION_H

#include "GameConfig.h"
#include "gameitem.h"
#include "imageinitializer.h"

#include <QObject>
#include <stack>
#include <QPropertyAnimation>

class Unit;

class Action : public QObject
{
    Q_OBJECT
public:

    enum ActionType {
        Move=1,
        Attack=2
    };

    enum ActionStatus {
        Prepare=1,
        Running=2,
        End=3
    };

    explicit Action(QObject *parent = nullptr);

    virtual ~Action();

    virtual ActionType actionType() const = 0;

    virtual ActionStatus status() const = 0;

signals:
    void actionFinished();
};

class Move: public Action {
    Q_OBJECT
public:
    explicit Move(Unit *unit, QPoint target, std::stack<QPoint> route, QObject *parent = nullptr);

    ~Move();

    ActionType actionType() const override{
        return Action::Move;
    }

    ActionStatus status() const override{
        return m_status;
    }

public slots:
    void onAnimationFinish();

private:
    Unit* const m_unit;
    const QPoint m_target;
    ActionStatus m_status;
    std::stack<QPoint> m_route;
    QPropertyAnimation *m_animation;
    void NextAnimation();
};

class Attack: public Action {
    Q_OBJECT
public:
    explicit Attack(QObject *parent = nullptr);

    ~Attack();

    ActionType actionType() const override{
        return Action::Attack;
    }

    ActionStatus status() const override{
        return m_status;
    }

private:
    Unit *m_source, *m_target;
    ActionStatus m_status;
};

class Bullet: public GameItem {
    Q_OBJECT
public:
    enum BulletType {
        Explosion=1
    };

    explicit Bullet(QGraphicsItem *parent = nullptr);

    virtual ~Bullet();

    virtual BulletType bulletType() const = 0;
};

class Explosion: public Bullet {
    Q_OBJECT
public:
    explicit Explosion(QGraphicsItem *parent = nullptr);

    ~Explosion();

    BulletType bulletType() const override{
        return Bullet::Explosion;
    }

private:
    static const Image* m_image;
    const Image* image() const override;
    friend void ImageInitializer::ImageInitial();
};

#endif // ACTION_H
