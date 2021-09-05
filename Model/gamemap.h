#ifndef MAP_H
#define MAP_H

#include <QObject>

#include "GameConfig.h"
#include "image.h"
#include "imageinitializer.h"

class Block;

class GameMap : public QObject
{
    Q_OBJECT
public:
    explicit GameMap(QGraphicsScene *scene, QObject *parent = nullptr);
    Block** operator[](int x) {
        return m_pBlocks[x];
    }

signals:

private:
    Block* m_pBlocks[NUMX+2][NUMY+2];
};

class Block: public GameItem {
    Q_OBJECT
public:
    enum BlockType {
        Dirt=1,
        Lava=2
    };

    explicit Block(QGraphicsItem *parent = nullptr): GameItem(parent) {}

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    virtual BlockType blockType() const = 0;

protected slots:
    void onframeChange(int frameCount);
};

class Dirt: public Block {
    Q_OBJECT
public:
    explicit Dirt(QGraphicsItem *parent = nullptr);

    ~Dirt();

    BlockType blockType() const override;

protected:
    const Image* image() const override;

private:
    static Image* m_image;

public:
    friend void ImageInitializer::ImageInitial();
};

class Lava: public Block {
    Q_OBJECT
public:
    explicit Lava(QGraphicsItem *parent = nullptr);

    ~Lava();

    BlockType blockType() const override;

protected:
    const Image* image() const override;

private:
    static Image* m_image;

public:
    friend void ImageInitializer::ImageInitial();
};

#endif // MAP_H
