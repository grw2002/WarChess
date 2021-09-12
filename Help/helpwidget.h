#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QTextBrowser>
#include <QWidget>


namespace Ui {
class HelpWidget;
}

/**
 * @brief 帮助界面，借助了小作业中“图片按钮”的实现
 */
class HelpWidget : public QWidget {
  Q_OBJECT

public:
  explicit HelpWidget(QWidget *parent = nullptr);
  ~HelpWidget();

protected:
  bool eventFilter(QObject *, QEvent *) override;

private:
  void setPic();

private:
  Ui::HelpWidget *ui;
  int m_nCount;
};

#endif // HELPWIDGET_H
