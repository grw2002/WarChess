#include "mainwindow.h"
#include "gamescene.h"
#include "ui_mainwindow.h"


#include <QGraphicsScene>
#include <QGraphicsView>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  m_gameView = new GameView(ui->centralwidget);
  m_gameView->setObjectName(QString::fromUtf8("GameView"));
  m_gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_gameView->setDragMode(QGraphicsView::ScrollHandDrag);
  m_gameView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  m_gameView->setFixedSize(QSize(VIEW_WIDTH, VIEW_HEIGHT));
  ui->horizontalLayout->addWidget(m_gameView);

  m_game = new GameMain(m_gameView, this);
  m_gameView->setScene(m_game->scene());

  //    s=new GameScene(this);
  //    s->addLine(0,0,2000,1000);
  //    s->addRect(0,0,100,50);
  //    m_gameView->setScene(s);
}

MainWindow::~MainWindow() {
  delete m_game;
  delete m_gameView;
  delete ui;
}
