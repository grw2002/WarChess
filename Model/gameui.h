#ifndef GAMEUI_H
#define GAMEUI_H

#include "GameConfig.h"
#include "gameitem.h"
#include "imageinitializer.h"

#include <QObject>
#include <vector>

/**
 * @brief The GameUI class 所有UI的基类
 */
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
    UnitAttack = 7,
    Logo = 8
  };

  explicit GameUI(QGraphicsItem *parent = nullptr);

  virtual ~GameUI();

  virtual UIType uiType() const = 0;

protected:
  void onClick(QGraphicsSceneMouseEvent *event) override;

signals:
  void GameUIClosed(GameUI *gameui);

private:
  friend class Unit;
};

/**
 * @brief 单位信息（悬浮窗），与Unit的hover事件挂钩
 */

class UnitStatus : public GameUI {
  Q_OBJECT
public:
  UnitStatus(Unit *unit, QGraphicsItem *parent = nullptr);

  ~UnitStatus();

  UIType uiType() const override;

protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) override;

  virtual QRectF boundingRect() const override;

  virtual void onClick(QGraphicsSceneMouseEvent *event) override;

  const Image *image() const override;

private:
  /**
   * @brief unitType 工具函数，进行UnitType到const char*的转换
   * @return
   */
  const char *unitType() const;

private:
  Unit *m_unit;
  QGraphicsTextItem *m_infoBox; // 文字信息
  static const Image *m_book;   // 框架图像

  friend void ImageInitializer::ImageInitial();
  friend class Unit;
};

/**
 * @brief 可视化Unit的可移动范围，并且响应点击事件
 */

class UnitMove : public GameUI {
  Q_OBJECT
public:
  explicit UnitMove(Unit *unit, std::vector<QPoint> dests,
                    QGraphicsItem *parent = nullptr);

  ~UnitMove();

  UIType uiType() const override;

protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) override;

  virtual QRectF boundingRect() const override;

  const Image *image() const override;

  virtual void onClick(QGraphicsSceneMouseEvent *event) override;

private:
  Unit *m_unit;
  std::vector<QPoint> m_dests; // 可达范围
  friend class UnitController;
  friend class Unit;
  friend class GameItem;
};

/**
 * @brief The UnitAttack class 攻击范围选择
 */

class UnitAttack : public GameUI {
  Q_OBJECT
public:
  explicit UnitAttack(Unit *unit, std::vector<QPoint> range,
                      std::vector<Unit *> targets,
                      QGraphicsItem *parent = nullptr);

  ~UnitAttack();

  UIType uiType() const override;

protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) override;

  virtual QRectF boundingRect() const override;

  const Image *image() const override;

  virtual void onClick(QGraphicsSceneMouseEvent *event) override;

private:
  Unit *m_unit;
  std::vector<QPoint> m_range;
  std::vector<Unit *> m_targets;

  friend class UnitController;
  friend class Unit;
  friend class GameItem;
};

/**
 * @brief The UnitHP class 血条
 */

class UnitHP : public GameUI {
  Q_OBJECT
public:
  explicit UnitHP(Unit *unit, QGraphicsItem *parent = nullptr);

  ~UnitHP();

  UIType uiType() const override;

protected:
  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  const Image *image() const override;

private:
  static const QRectF sm_bounding;
  Unit *const m_unit;
};

/**
 * @brief The UnitActionMenu class 选择Unit的动作（攻击？移动？）
 */

class UnitActionMenu : public GameUI {
  Q_OBJECT
public:
  explicit UnitActionMenu(Unit *unit, QGraphicsItem *parent = nullptr);

  ~UnitActionMenu();

  UIType uiType() const override;

public slots:
  /**
   * @brief onIconClick 点击按钮之后使用槽来接收返回值
   */
  void onIconClick(int);

protected:
  const Image *image() const override;

  virtual void onClick(QGraphicsSceneMouseEvent *event) override;

private:
  // 各种各样的图标
  static const Image *sm_backgroundImage;
  static const Image *sm_walkIcon, *sm_attackIcon;
  static const Image *sm_sword, *sm_axe, *sm_tnt;
  Unit *m_unit;
  std::vector<QGraphicsItem *> m_icons;

  friend class ImageInitializer;
  friend class GameItem;
  friend class UnitController;
};

/**
 * @brief The GameIcon class
 * 图标类，传入一个int，通过一个signal“回调”这个值，可以自定义图标
 */

class GameIcon : public GameUI {
  Q_OBJECT
public:
  explicit GameIcon(const Image *image, int nCallbackValue = 0,
                    QGraphicsItem *parent = nullptr);

  ~GameIcon();

  UIType uiType() const override;

protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) override;

  const Image *image() const override;

  virtual void onClick(QGraphicsSceneMouseEvent *event) override;

  /**
   * @brief hoverEnterEvent 通过hover来优化按钮视觉体验
   * @param event
   */
  virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

  virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

  /**
   * @brief GameIcon::sceneEventFilter
   * 如果要画文字，那么可能会出现重叠，所以需要用sceneEventFilter把点击事件导入到按钮这里来处理
   * @param obj
   * @param e
   * @return
   */
  bool sceneEventFilter(QGraphicsItem *watched, QEvent *event) override;

signals:
  void IconClicked(int);

private:
  static const Image *sm_containerImage1, *sm_containerImage2;
  const Image *m_image;
  const Image *m_icon;
  int m_nCallbackValue; // 回调值

  friend class ImageInitializer;
  friend class GameItem;
};

/**
 * @brief The Logo class 大Logo
 */

class Logo : public GameUI {
  Q_OBJECT
public:
  explicit Logo(QGraphicsItem *parent = nullptr);

  ~Logo();

  UIType uiType() const override;

  const Image *image() const override;

private:
  static const Image *sm_logo;
  friend class ImageInitializer;
};

#endif // GAMEUI_H
