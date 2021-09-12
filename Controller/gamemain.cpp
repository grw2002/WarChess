#include "gamemain.h"
#include "action.h"
#include "gamecontroller.h"
#include "gamescene.h"
#include "gameui.h"
#include "gameview.h"
#include "imageinitializer.h"
#include "level.h"
#include "soundinitializer.h"
#include "unit.h"
#include "unitcontroller.h"


#include <QLabel>

GameMain::GameMain(GameView *gameview, QObject *parent)
    : QObject(parent), m_pOverlayUI(nullptr), m_pLevel(nullptr),
      m_status(Start), m_bAction(false), m_pCurrentAction(nullptr) {
  // 加载资源
  ImageInitializer::ImageInitial();
  SoundInitializer::SoundInitial();

  // 背景音乐
  m_playlist = new QMediaPlaylist(this);
  m_playlist->addMedia(QUrl("qrc:/sound/bgm/bgm.mp3"));
  m_playlist->addMedia(QUrl("qrc:/sound/bgm/bgm2.mp3"));
  m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
  m_playlist->setCurrentIndex(0);
  m_player = new QMediaPlayer(this);
  m_player->setPlaylist(m_playlist);
  m_player->play();

  // 加载主场景
  m_scene = new GameScene(this, gameview);
  m_scene->addRect(0, 0, MAP_WIDTH, MAP_HEIGHT);

  // 加载侧边栏
  loadSidebar();

  // 全局随机数
  srand(time(NULL));

  // 进入开始界面
  onLevelStateChange(1);
}

void GameMain::loadSidebar() {
  m_sidebar = new QWidget();
  m_sidebarLayout = new QVBoxLayout(m_sidebar);
  m_sidebarTitle = new QLabel(m_sidebar);
  m_sidebarSide = new QLabel(m_sidebar);
  m_sidebarInfo = new QLabel(m_sidebar);
  m_sidebarBacktoHome = new QPushButton("返回主界面", m_sidebar);
  m_sidebarLayout->addWidget(m_sidebarTitle, 0, Qt::AlignCenter);
  m_sidebarLayout->addWidget(m_sidebarSide, 0, Qt::AlignCenter);
  m_sidebarLayout->addWidget(m_sidebarInfo, 0, Qt::AlignCenter);
  m_sidebarLayout->addStretch(1);
  m_sidebarLayout->addWidget(m_sidebarBacktoHome, 0, Qt::AlignCenter);
  m_sidebarLayout->setAlignment(Qt::AlignTop);
  m_sidebarTitle->setFont(QFont("黑体", 24));
  m_sidebarTitle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  m_sidebarSide->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  m_sidebarTitle->setFixedHeight(100);
  m_sidebarSide->setFixedHeight(50);
  m_sidebarInfo->setFixedHeight(200);
  m_sidebarBacktoHome->installEventFilter(this);

  m_sidebar->setFixedWidth(0);
  m_sidebarTitle->setText("");
  m_sidebarSide->setText("");
  m_sidebarInfo->setText("");
}

void GameMain::onLevelStateChange(int x) {
  if (m_pLevel) {
    delete m_pLevel;
  }
  m_bAction = false;
  m_pCurrentAction = nullptr;
  switch (x) {
  case 1: { // 开始界面
    m_sidebar->setFixedWidth(0);

    auto &level = m_pLevel;
    level = new StartScreen(this, this);
    level->InitMap();
    level->InitUnit();
    connect(level, SIGNAL(LevelStateChanged(int)), this,
            SLOT(onLevelStateChange(int)));
    break;
  }
  case 2: { // 结束界面（胜利）
    m_sidebar->setFixedWidth(0);
    m_sidebarTitle->setText("");
    m_sidebarSide->setText("");
    m_sidebarInfo->setText("");

    auto &level = m_pLevel;
    level = new EndScreen(true, this, this);
    level->InitMap();
    level->InitUnit();
    connect(level, SIGNAL(LevelStateChanged(int)), this,
            SLOT(onLevelStateChange(int)));
    break;
  }
  case 3: { // 结束界面（失败）
    m_sidebar->setFixedWidth(0);
    m_sidebarTitle->setText("");
    m_sidebarSide->setText("");
    m_sidebarInfo->setText("");

    auto &level = m_pLevel;
    level = new EndScreen(false, this, this);
    level->InitMap();
    level->InitUnit();
    connect(level, SIGNAL(LevelStateChanged(int)), this,
            SLOT(onLevelStateChange(int)));
    break;
  }
  case 4: { // 遭遇战
    m_sidebar->setFixedWidth(256);
    m_sidebarTitle->setText("遭遇战");
    m_sidebarInfo->setText("");

    m_status = Self;
    m_pLevel = new Encounter(this, this);
    m_pLevel->InitMap();
    m_pLevel->InitUnit();
    connect(m_pLevel, SIGNAL(LevelStateChanged(int)), this,
            SLOT(onLevelStateChange(int)));
    GameController::nextRound(this, GameMain::Self);
    break;
  }
  case 5: { // 村庄保卫战
    m_sidebar->setFixedWidth(256);
    m_sidebarTitle->setText("村庄保卫战");
    m_sidebarInfo->setText("");

    m_status = Self;
    m_pLevel = new Assault(this, this);
    m_pLevel->InitMap();
    m_pLevel->InitUnit();
    connect(m_pLevel, SIGNAL(LevelStateChanged(int)), this,
            SLOT(onLevelStateChange(int)));
    GameController::nextRound(this, GameMain::Self);
    break;
  }
  default: {
    break;
  }
  }
}

bool GameMain::eventFilter(QObject *obj, QEvent *e) {
  // 侧边栏返回主界面
  if (obj == m_sidebarBacktoHome && e->type() == QEvent::MouseButtonRelease) {
    onLevelStateChange(1);
    return true;
  }
  return QObject::eventFilter(obj, e);
}

GameScene *GameMain::scene() const { return m_scene; }

QWidget *GameMain::sidebar() const { return m_sidebar; }

void GameMain::onActionFinish() { GameController::finishCurrentAction(this); }

bool GameMain::actioning() const { return m_bAction; }

GameMain::GameStatus GameMain::status() const { return m_status; }
