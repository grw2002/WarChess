#include "mainwindow.h"
#include "gamescene.h"
#include "helpwidget.h"
#include "ui_mainwindow.h"


#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>

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

  /*
   * 启动游戏
   */
  m_game = new GameMain(m_gameView, this);
  m_gameView->setScene(m_game->scene());

  m_game->sidebar()->setParent(ui->centralwidget);
  ui->horizontalLayout->addWidget(m_game->sidebar());
}

MainWindow::~MainWindow() {
  delete m_game;
  delete m_gameView;
  delete ui;
}

void MainWindow::on_help_triggered() {
  auto help = new HelpWidget();
  help->setAttribute(Qt::WA_DeleteOnClose);
  help->show();
}

void MainWindow::on_about_triggered() {
  QMessageBox::information(
      this, "关于",
      QString("村庄与掠夺2（Village&PillageⅡ）") + '\n' +
          QString("未央-软件01 郭镕玮 grw20@mails.tsinghua.edu.cn") + '\n' +
          QString("2021夏 程序设计实训 大作业") + '\n' + QString("致谢：") +
          '\n' + QString("徐枫 老师") + '\n' +
          QString("唐瑞杰 助教  郑成伟 助教"));
}
