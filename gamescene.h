#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <math.h>
#include "ball.h"
#include "pad.h"

class ball;
class Pad;

class GameScene : public QGraphicsScene
{
    Q_OBJECT
    void setupBall();
    void setupPad();
    void moveBall();
    int m_timer;
    bool m_paused;
    ball* mBall;
    Pad* mPad;
private slots:
    void togglePause();
protected:
    void timerEvent(QTimerEvent* event);
public:
    typedef enum
        {
        BrickItem = QGraphicsItem::UserType + 1,
        BallItem,
        PadItem,
        ParticleItem
        } ItemTypes;
    GameScene();
    void setup();
    static const int Width = 800;
    static const int Height = 600;
    static const int GameTick = 1000 / 35 ;    // ms

};

#endif // GAMESCENE_H
