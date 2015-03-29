#include "gamescene.h"
#include "ball.h"
#include "pad.h"
#include <QTime>
#include <QColor>
#include <QtDebug>
#include <QPainter>
#include <QGraphicsView>

GameScene::GameScene(): m_paused(false)
{
    setSceneRect( -Width/2, -Height/2, Width, Height );
    const qreal borderWidth = 10;
    QPen pen(Qt::black);
    pen.setWidthF( borderWidth );
    QRectF borderRect = sceneRect().adjusted( -borderWidth/2, -borderWidth/2, borderWidth/2, borderWidth/2);
    addRect( borderRect, pen, Qt::white );
    setItemIndexMethod(QGraphicsScene::NoIndex);
}

void GameScene::setupBall()
{
    mBall = new ball(0, height()/12);
    mBall->start( 6*M_PI/4 - qrand() * M_PI/2 / RAND_MAX );
    addItem( mBall );
}

void GameScene::setupPad()
{
        mPad = new Pad( -Pad::Width/2, Height/2 - 50 );
        addItem( mPad );
        mPad->grabMouse();
        mPad->grabKeyboard();
        connect( mPad, SIGNAL(pausePressed()), SLOT(togglePause()) );
}

void GameScene::setup()
{
    setupBall();
    setupPad();
    m_timer = startTimer( GameTick );
}

void GameScene::moveBall()
{
    mBall->updatePos( GameTick );
    qreal time = GameTick;
    bool rebound = true;
    int rebounds = 0;
    while( rebound && time > 0 )
        {
        rebound = false;
        QPointF impact;
        if( mBall->bounceWalls( time, impact ) )
            {
            rebound = true;
            }
        if( rebound )
            {
            rebounds++;
            mBall->updatePos( time );
            }
        }
}
void GameScene::timerEvent(QTimerEvent */*event*/)
{
    moveBall();
}
void GameScene::togglePause()
{
    if( !m_paused )
            mBall->stop();
    else
            mBall->resume();
    m_paused = !m_paused;
}
