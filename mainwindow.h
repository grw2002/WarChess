#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gameview.h"
#include "gamescene.h"

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsView *gameView;
    QGraphicsScene *s;
};
#endif // MAINWINDOW_H
