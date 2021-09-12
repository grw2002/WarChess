#ifndef GAMEMAIN_H
#define GAMEMAIN_H

#include "GameConfig.h"
#include "gameitem.h"

#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <vector>


#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSoundEffect>


class UnitController;

class GameMain : public QObject {
  Q_OBJECT
public:
  enum GameStatus { Start = 0, End = 1, Self = 2, Enemy = 3, Friend = 4 };

  explicit GameMain(GameView *gameview = nullptr, QObject *parent = nullptr);

  /**
   * @brief scene 获取主场景
   * @return 主场景
   */
  GameScene *scene() const;

  /**
   * @brief sidebar 获取侧边栏
   * @return 侧边栏
   */
  QWidget *sidebar() const;

  /**
   * @brief Actioning 是否有活动的Action
   * @return
   */
  bool actioning() const;

  /**
   * @brief status 游戏状态
   * @return GameMain::GameStatus
   */
  GameStatus status() const;

public slots:
  /**
   * @brief onActionFinish 结束活动Action
   */
  void onActionFinish();

  /**
   * @brief onLevelStateChange 切换游戏状态
   */
  void onLevelStateChange(int);

public:
  GameUI *m_pOverlayUI; // 当前覆盖全局的UI
  QLabel *m_sidebarTitle, *m_sidebarSide, *m_sidebarInfo; // 侧边栏
  QPushButton *m_sidebarBacktoHome;

protected:
  bool eventFilter(QObject *obj, QEvent *e) override;

private:
  /**
   * @brief loadSidebar 加载侧边栏
   */
  void loadSidebar();

private:
  Level *m_pLevel;             // 当前关卡
  std::vector<Unit *> m_units; // 所有单位
  GameStatus m_status;         // 游戏状态
  bool m_bAction;              // 是否有活动Action
  Action *m_pCurrentAction;    // 活动Action的指针
  GameScene *m_scene;          // 当前场景

  // 侧边栏
  QWidget *m_sidebar;
  QVBoxLayout *m_sidebarLayout;

  // 背景音乐
  QMediaPlaylist *m_playlist;
  QMediaPlayer *m_player;

  friend class UnitController;
  friend class MapController;
  friend class GameController;
  friend class Level;
  friend class Encounter;
  friend class Assault;
};

#endif // GAMEMAIN_H
