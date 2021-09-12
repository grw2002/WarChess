#ifndef IMAGE_H
#define IMAGE_H

#include "GameConfig.h"

#include <QImage>
#include <QMovie>
#include <QObject>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

/**
 * @brief
 * 自行定义的图像类，可以一站式处理paint、boundingrect、jpg、gif等多个问题
 */
class Image : public QObject {
  Q_OBJECT
public:
  /**
   * @brief Image
   * @param path 路径
   * @param width 宽度
   * @param height 高度
   * @param isGif 是否是gif
   * @param anchor 锚点
   * @param horizonMirrored 水平镜像
   * @param parent
   */
  Image(const QString &path, int width, int height, bool isGif = false,
        QPoint anchor = QPoint(0, 0), bool horizonMirrored = false,
        QObject *parent = nullptr);

  virtual ~Image();

  /**
   * @brief boundingRect 同QGraphicsItem::boundingRect，直接传参即可
   * @return
   */
  QRectF boundingRect() const;

  /**
   * @brief paint 同QGraphicsItem::paint，直接传参即可
   * @param painter
   * @param option
   * @param widget
   * @param horizonMirrored
   */
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget, bool horizonMirrored = false) const;

private:
  QImage *m_image;
  QMovie *m_movie;
  const QPoint m_anchor; // 锚点
  const int m_width, m_height;
  const QRectF m_bounding;
  const bool m_bGif;
  const bool m_horizonMirrored;

signals:
  /**
   * @brief frameChanged gif刷新，需要GameItem::update()
   */
  void frameChanged(int);
};

#endif // IMAGE_H
