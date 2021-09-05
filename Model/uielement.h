#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <QObject>

class UIElement : public QObject
{
    Q_OBJECT
public:
    explicit UIElement(QObject *parent = nullptr);

signals:

};

#endif // UIELEMENT_H
