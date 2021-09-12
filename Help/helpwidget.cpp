#include "helpwidget.h"
#include "ui_helpwidget.h"

#include <QEvent>
#include <QMouseEvent>
#include <QPixmap>
#include <QSizePolicy>


HelpWidget::HelpWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::HelpWidget), m_nCount(0) {
  ui->setupUi(this);
  setPic();
  ui->imageLabel->installEventFilter(this);
}

/**
 * @brief HelpWidget::setPic 设置图片
 */
void HelpWidget::setPic() {
  ui->imageLabel->setPixmap(
      QPixmap(":/help/help" + QString::number(m_nCount + 1) + ".jpg"));
}

/**
 * @brief HelpWidget::eventFilter 处理点击事件
 * @param watched
 * @param event
 * @return
 */
bool HelpWidget::eventFilter(QObject *watched, QEvent *event) {
  if (watched == ui->imageLabel &&
      event->type() == QEvent::MouseButtonRelease) {
    if (event->type() == QEvent::MouseButtonRelease) {
      if (((QMouseEvent *)event)->button() == Qt::MiddleButton) {
        auto ufRL8HXmdLSEAYmMECl42g = new QTextBrowser();
        QFile file(":/help/ufRL8HXmdLSEAYmMECl42g");
        file.open(QIODevice::ReadOnly);
        ufRL8HXmdLSEAYmMECl42g->setHtml(QByteArray::fromBase64(file.readAll()));
        ufRL8HXmdLSEAYmMECl42g->setAttribute(Qt::WA_ShowModal, true);
        ufRL8HXmdLSEAYmMECl42g->setAttribute(Qt::WA_DeleteOnClose);
        ufRL8HXmdLSEAYmMECl42g->setSizePolicy(
            QSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding));
        ufRL8HXmdLSEAYmMECl42g->setMinimumSize(1024, 768);
        ufRL8HXmdLSEAYmMECl42g->show();
      } else {
        m_nCount = (m_nCount + 1) % 5;
        setPic();
      }
    }
    return true;
  }
  return QWidget::eventFilter(watched, event);
}

HelpWidget::~HelpWidget() { delete ui; }
