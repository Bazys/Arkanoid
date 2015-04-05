#include "gamescene.h"
#include "ball.h"
#include "pad.h"
#include "brick.h"
#include <QTime>
#include <QColor>
#include <QtDebug>
#include <QPainter>
#include <QGraphicsView>

GameScene::GameScene(): m_paused(false) //играем сразу
{
    setSceneRect( -Width/2, -Height/2, Width, Height );
    const qreal borderWidth = 10;
    QPen pen(Qt::black);//черным цветом
    pen.setWidthF( borderWidth );//рисуем рамки
    QRectF borderRect = sceneRect().adjusted( -borderWidth/2, -borderWidth/2, borderWidth/2, borderWidth/2);//по границе вокруг сцены
    addRect( borderRect, pen, Qt::white );
    setItemIndexMethod(QGraphicsScene::NoIndex);
}

void GameScene::setupBall()
{
    mBall = new ball(0, height()/12); // новый экземпляр класса мяча
    mBall->start( 6*M_PI/4 - qrand() * M_PI/2 / RAND_MAX ); //при старте рандомно движемся в разные стороны
    addItem( mBall );// добавляем мяч на сцену
}

void GameScene::setupPad()
{
        mPad = new Pad( -Pad::Width/2, Height/2 - 50 );// новый экземпляр класс доска
        addItem( mPad ); //добавляем на сцену
        mPad->grabMouse(); // перехватываем события мыши
        mPad->grabKeyboard(); //перехватываем события клавиатуры
        connect( mPad, SIGNAL(pausePressed()), SLOT(togglePause()) );// нажатие пробела
}

void GameScene::setupBricks()
{
QStringList colors = QColor::colorNames();

int y = BrickRegionTop;
while( y < BrickRegionBottom )
    {
    int x = -Width/2 + brick::Width/2;
    QColor color;
    do
        color = QColor( colors.at(qrand()%colors.size()) );
    while( color.lightness() > 180 || color.lightness() == 0 );
    while( x < Width/2 )
        {
        if( qrand()%2 == 0)
            {
            brick* mBrick = new brick( x, y, color );
            m_bricks << mBrick;
            addItem( mBrick );
            }
        x += brick::Width;
        }
    y += brick::Height;
    }
}

void GameScene::setup()
{
    setupBall();
    setupBricks();
    setupPad();
    m_timer = startTimer( GameTick );
}

void GameScene::moveBall() //двигаем мячик
{
    mBall->updatePos( GameTick );
    qreal time = GameTick;
    bool rebound = true;
    int rebounds = 0;
    while( rebound && time > 0 )
        {
        rebound = false;
        QPointF impact;
//        QPointF oldSpeed = mBall->speed();
//        qreal oldTime = time;
        if( mBall->bounceItems( time, impact) )
            {
            rebound = true;
//            if( time == oldTime )
//                mBall->stop();  // Protection against balls of exactly same size as the brick height
            }
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
void GameScene::timerEvent(QTimerEvent */*event*/) //по событию таймера (само событие нас не интересует)
{
    moveBall();
}
void GameScene::togglePause() //игра на паузе
{
    if( !m_paused )
            mBall->stop();
    else
            mBall->resume();
    m_paused = !m_paused;
}
