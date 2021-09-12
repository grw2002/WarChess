#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamemain.h"
#include "gamescene.h"
#include "gameview.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The MainWindow class
 */

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_help_triggered();

  void on_about_triggered();

private:
  Ui::MainWindow *ui;
  GameView *m_gameView;
  GameMain *m_game;
};
#endif // MAINWINDOW_H
