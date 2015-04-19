#ifndef BRICK_H
#define BRICK_H
#include "gamescene.h"
#include <QColor>
#include <QGraphicsRectItem>

class Brick : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    QColor m_color;
    bool m_destroyed;
public:
    Brick(int aX, int aY, QColor aColor = Qt::red );
    bool destroyed() { return m_destroyed; }
    enum { Type = GameScene::BrickItem };
    int type() const { return Type; }
    void destroy();
    static const int Width = 50;
    static const int Height = 20;
};
#endif // BRICK_H
