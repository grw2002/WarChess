#ifndef LEVEL_H
#define LEVEL_H

#include "GameConfig.h"
#include "gamemain.h"
#include "imageinitializer.h"
#include "unit.h"


#include <QObject>
#include <vector>

/**
 * @brief The Level class 所有关卡的基类
 */

class Level : public QObject {
  Q_OBJECT
public:
  enum LevelType { Encounter = 1, Assault = 2, Start = 3, End = 4 };

  explicit Level(GameMain *game, QObject *parent = nullptr);

  virtual ~Level();

  virtual LevelType levelType() const = 0;

  /**
   * @brief InitMap 初始化地图
   */
  virtual void InitMap() = 0;

  /**
   * @brief InitUnit 初始化Unit
   */
  virtual void InitUnit() = 0;

  /**
   * @brief VictoryJudge
   * @return 0-未决出胜负，1-胜利，2-失败
   */
  virtual int VictoryJudge() = 0;

  /**
   * @brief NextStage 在我方/敌方完成一轮攻击后调用，主要用于村庄保卫战
   * @param game
   * @param prev
   * @param nex
   * @return
   */
  virtual bool NextStage(GameMain *game, GameMain::GameStatus prev,
                         GameMain::GameStatus nex);

signals:
  /**
   * @brief LevelStateChanged 关卡结束（胜利/失败）
   */
  void LevelStateChanged(int);

protected:
  /**
   * @brief ability
   * 返回从UnitType到Ability的映射，用于每一关自定义各种Unit的属性
   * @return
   */
  virtual Ability ability(Unit::UnitType) const = 0;

protected:
  GameMain *m_pGame;
  GameMap *m_pMap;

  friend class GameController;
  friend class MapController;
  friend class UnitController;
};

/**
 * @brief The Encounter class 遭遇战
 */

class Encounter : public Level {
  Q_OBJECT
public:
  explicit Encounter(GameMain *game, QObject *parent = nullptr);

  ~Encounter();

  LevelType levelType() const override;

  void InitMap() override;

  void InitUnit() override;

  int VictoryJudge() override;

  Ability ability(Unit::UnitType) const override;
};

/**
 * @brief The Assault class 村庄保卫战
 */

class Assault : public Level {
  Q_OBJECT
public:
  explicit Assault(GameMain *game, QObject *parent = nullptr);

  ~Assault();

  LevelType levelType() const override;

  void InitMap() override;

  void InitUnit() override;

  int VictoryJudge() override;

  Ability ability(Unit::UnitType) const override;

  bool NextStage(GameMain *game, GameMain::GameStatus prev,
                 GameMain::GameStatus nex) override;

private:
  int m_nRoundCount;
};

/**
 * @brief The StartScreen class 开始界面
 */

class StartScreen : public Level {
  Q_OBJECT
public:
  explicit StartScreen(GameMain *game, QObject *parent = nullptr);

  ~StartScreen();

  LevelType levelType() const override;

  void InitMap() override;

  void InitUnit() override;

  /**
   * @brief VictoryJudge
   * @return
   */
  int VictoryJudge() override;

  /**
   * @brief ability 这个函数不应当被调用
   * @return
   */
  Ability ability(Unit::UnitType) const override;

public slots:
  /**
   * @brief startGame 用于接收按钮的回调
   */
  void startGame(int);

private:
  static const Image *sm_starticon;
  GameUI *m_startEncounter, *m_startAssault, *m_logo;
  QGraphicsSimpleTextItem *m_textEncounter, *m_textAssault;
  friend class ImageInitializer;
};

/**
 * @brief The EndScreen class 结束界面
 */

class EndScreen : public Level {
  Q_OBJECT
public:
  explicit EndScreen(bool victory, GameMain *game, QObject *parent = nullptr);

  ~EndScreen();

  LevelType levelType() const override { return Level::End; }

  void InitMap() override;

  void InitUnit() override;

  /**
   * @brief VictoryJudge 这个函数不应当被调用
   * @return
   */
  int VictoryJudge() override;

  /**
   * @brief ability 这个函数不应当被调用
   * @return
   */
  Ability ability(Unit::UnitType) const override;

public slots:
  /**
   * @brief backToHome 用于接收按钮的回调
   */
  void backToHome(int);

private:
  static const Image *sm_starticon;
  GameUI *m_backToHome;
  QGraphicsSimpleTextItem *m_textHome, *m_title;
  bool m_bVictory;
  friend class ImageInitializer;
};

#endif // LEVEL_H
