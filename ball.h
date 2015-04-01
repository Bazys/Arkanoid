#ifndef BALL_H
#define BALL_H

#include "gamescene.h"
#include <QPair>
#include <QPainterPath>
#include <QGraphicsEllipseItem>


class ball : public QGraphicsEllipseItem
{
    QColor m_color;
    QPointF m_speed;    // Vector
    bool m_moving;
public:
    ball(int aX, int aY);
    enum { Type = GameScene::BallItem };
    int type() const { return Type; }
    static const qreal Radius;
    static const qreal LinSpeed;
    QPointF speed() { return m_speed; } //Getter
    void stop() { m_moving = false; }
    void resume() { m_moving = true; }
    void start(qreal aAngle);
    void updatePos(qreal aTime);
    bool bounceWalls( qreal& aTime, QPointF& aImpact );
    bool bounceItems( qreal& aTime, QPointF& aImpactPoint);
};

#endif // BALL_H
