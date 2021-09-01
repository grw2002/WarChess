#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamescene.h"

#include <QGraphicsView>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gameView = new GameView(ui->centralwidget);
    gameView->setObjectName(QString::fromUtf8("GameView"));
    gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->horizontalLayout->addWidget(gameView);

    s=new GameScene(this);
    s->addLine(0,0,2000,1000);
    s->addRect(0,0,100,50);
    gameView->setScene(s);
}

MainWindow::~MainWindow()
{
    delete gameView;
    delete ui;
}

