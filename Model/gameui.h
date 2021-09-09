#ifndef GAMEUI_H
#define GAMEUI_H

#include "GameConfig.h"
#include "gameitem.h"
#include "imageinitializer.h"

//#include "action.h"

#include <QObject>
#include <vector>

class GameUI : public GameItem {
  Q_OBJECT
public:
  enum UIType {
    UnitStatus = 1,
    GameInfo = 2,
    UnitMove = 3,
    UnitHP = 4,
    UnitActionMenu = 5,
    Icon = 6,
    UnitAttack = 7
  };

  GameUI(QGraphicsItem *parent = nullptr);

  virtual ~GameUI();

  virtual UIType uiType() const = 0;

  friend class Unit;

protected:
  void onClick(QGraphicsSceneMouseEvent *event) override {
    qDebug() << "gameui onclick" << event->pos();
  }

signals:
  void GameUIClosed(GameUI *gameui);
};

class UnitStatus : public GameUI {
  Q_OBJECT
public:
  UnitStatus(Unit *unit, QGraphicsItem *parent = nullptr);

  ~UnitStatus();

  UIType uiType() const override { return GameUI::UnitStatus; }

protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) override;

  virtual QRectF boundingRect() const override;

  virtual void onClick(QGraphicsSceneMouseEvent *event) override;

private:
  Unit *m_unit;
  QGraphicsTextItem *m_infoBox;
  const Image *image() const override;
  static const Image *m_book;
  friend void ImageInitializer::ImageInitial();
  const char *unitType() const;
  friend class Unit;
};

class UnitMove : public GameUI {
  Q_OBJECT
public:
  explicit UnitMove(Unit *unit, std::vector<QPoint> dests,
                    QGraphicsItem *parent = nullptr);

  ~UnitMove();

  UIType uiType() const override { return GameUI::UnitMove; }

signals:
  void DestSelected(QPoint target);

protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) override;

  virtual QRectF boundingRect() const override {
    return QRectF(0, 0, MAP_WIDTH, MAP_HEIGHT);
  }

  const Image *image() const override { return nullptr; }

  virtual void onClick(QGraphicsSceneMouseEvent *event) override;

  friend class Unit;
  friend class GameItem;

private:
  Unit *m_unit;
  std::vector<QPoint> m_dests;
  friend class UnitController;
};

class UnitAttack : public GameUI {
  Q_OBJECT
public:
  explicit UnitAttack(Unit *unit, std::vector<QPoint> range,
                      std::vector<Unit *> targets,
                      QGraphicsItem *parent = nullptr);

  ~UnitAttack();

  UIType uiType() const override { return GameUI::UnitAttack; }

signals:
  void DestSelected(QPoint target);

protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) override;

  virtual QRectF boundingRect() const override {
    return QRectF(0, 0, MAP_WIDTH, MAP_HEIGHT);
  }

  const Image *image() const override { return nullptr; }

  virtual void onClick(QGraphicsSceneMouseEvent *event) override;

  friend class Unit;
  friend class GameItem;

private:
  Unit *m_unit;
  std::vector<QPoint> m_range;
  std::vector<Unit *> m_targets;
  friend class UnitController;
};

class UnitHP : public GameUI {
  Q_OBJECT
public:
  explicit UnitHP(Unit *unit, QGraphicsItem *parent = nullptr);

  ~UnitHP();

  UIType uiType() const override { return GameUI::UnitHP; }

protected:
  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  const Image *image() const override { return nullptr; }

private:
  static const QRectF sm_bounding;
  Unit *const m_unit;
};

class UnitActionMenu : public GameUI {
  Q_OBJECT
public:
  explicit UnitActionMenu(Unit *unit, QGraphicsItem *parent = nullptr);

  ~UnitActionMenu();

  UIType uiType() const override { return GameUI::UnitActionMenu; }

public slots:
  void onIconClick(int);

protected:
  const Image *image() const override { return sm_backgroundImage; }

  virtual void onClick(QGraphicsSceneMouseEvent *event) override;

private:
  static const Image *sm_backgroundImage;
  static const Image *sm_walkIcon, *sm_attackIcon;
  static const Image *sm_sword, *sm_axe, *sm_tnt;
  Unit *m_unit;
  std::vector<QGraphicsItem *> m_icons;
  friend class ImageInitializer;
  friend class GameItem;
  friend class UnitController;
};

class GameIcon : public GameUI {
  Q_OBJECT
public:
  explicit GameIcon(const Image *image, int nCallbackValue = 0,
                    QGraphicsItem *parent = nullptr);

  ~GameIcon();

  UIType uiType() const override { return GameUI::Icon; }

protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) override;

  const Image *image() const override { return sm_containerImage1; }

  virtual void onClick(QGraphicsSceneMouseEvent *event) override {
    Q_UNUSED(event);
    emit IconClicked(m_nCallbackValue);
  }

signals:
  void IconClicked(int);

private:
  static const Image *sm_containerImage1, *sm_containerImage2;
  const Image *m_icon;
  int m_nCallbackValue;
  friend class ImageInitializer;
};

class GameInfo : public GameUI {
  Q_OBJECT
public:
  GameInfo(QGraphicsItem *parent = nullptr);

  ~GameInfo();

  UIType uiType() const override { return GameUI::UnitStatus; }

protected:
};

#endif // GAMEUI_H
