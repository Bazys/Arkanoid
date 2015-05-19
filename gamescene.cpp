#include "gamescene.h"
#include "ball.h"
#define _USE_MATH_DEFINES
#include "pad.h"
#include "brick.h"
#include <math.h>
#include <QTime>
#include <QColor>
#include <QtDebug>
#include <QPainter>
#include <QGraphicsView>

GameScene::GameScene(): m_paused(true), m_tries(3), m_score(0) //не играем сразу, три попытки, 0 очков
{
    setSceneRect( -Width/2, -Height/2, Width, Height );
    const qreal borderWidth = 10;
    QPen pen(Qt::black);//черным цветом
    pen.setWidthF( borderWidth );//рисуем рамки
    QRectF borderRect = sceneRect().adjusted( -borderWidth/2, -borderWidth/2, borderWidth/2, borderWidth/2);//по границе вокруг сцены
    QBrush brush(QPixmap(":/res/arkanoid.png"));
    addRect( borderRect, pen, brush );
    scores = new QGraphicsSimpleTextItem( "0" );
    scores->setBrush( Qt::black );
    scores->setFont( QFont("Arial", 15, QFont::Bold) );
    scores->setPos( (Width/2)-20, (-Height/2)+10 );
    addItem(scores);
    label = new QGraphicsSimpleTextItem( QString::number(m_tries) );
    label->setBrush( Qt::black );
    label->setFont( QFont("Arial", 15, QFont::Bold) );
    label->setPos( (-Width/2)+20, (-Height/2)+10 );
    addItem(label);
    setItemIndexMethod(QGraphicsScene::NoIndex);
}

void GameScene::setupBall()
{
    mBall = new ball(0, height()/2-70, m_tries); // новый экземпляр класса мяча
    mBall->start( 6 * M_PI / 2 - qrand() * M_PI/2 / RAND_MAX, 1 ); //при старте рандомно движемся в разные стороны
    mBall->stop();
    addItem( mBall );// добавляем мяч на сцену
}

void GameScene::setupPad()
{
        mPad = new Pad( (-Pad::Width/2), Height/2 - 50 );// новый экземпляр класс доска
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
    int x = -Width/2 + Brick::Width/2;
    // рисуем разными цветами
    QColor color;
    do
        color = QColor( colors.at(qrand()%colors.size()) );
    while( color.lightness() > 180 || color.lightness() == 0 );
    while( x < Width/2 )
        {
        // рандомно рисуем или не рисуем кирпичи
        if( qrand()%2 == 0)
            {
            Brick* mBrick = new Brick( x, y, color );
            m_bricks << mBrick;
            addItem( mBrick );
            }
        x += Brick::Width;
        }
    y += Brick::Height;
}
}

void GameScene::setupHearts(int tries)
{
    foreach(QGraphicsSvgItem* heart, hearts){
        removeItem(heart);
    }
    hearts.clear();
    for (int i=0;i<tries;i++){
        QGraphicsSvgItem* mHearts = new QGraphicsSvgItem(":/res/heart.svg");
        mHearts->setFlags(QGraphicsItem::ItemClipsToShape);
        mHearts->setCacheMode(QGraphicsItem::NoCache);
        mHearts->setZValue(0);
        mHearts->setPos((-Width/2)+40+(i*30),(-Height/2)+10);
        hearts << mHearts;
        addItem(mHearts);
    }
}


void GameScene::setup()
{
    setupBall();
    setupBricks();
    setupPad();
    setupHearts(3);
    m_timer = startTimer( GameTick );
}

void GameScene::moveBall() //двигаем мячик
{
    mBall->updatePos( GameTick );
    if (m_tries != mBall->getTries()){ //только если изменилось кол-во попыток
        m_tries = mBall->getTries();
        QString tries = QString::number(m_tries);
        label->setText(tries);
        setupHearts(m_tries);
    }
    qreal time = GameTick;
    bool rebound = true;
    int rebounds = 0;
    while( rebound && time > 0 )
        {
        rebound = false;
        QPointF impact;
        Brick* hitBrick;
//        QPointF oldSpeed = mBall->speed();
        qreal oldTime = time;
        if( mBall->bounceItems( time, impact, hitBrick) )
            {
            rebound = true;
            QRectF brickRect;
            if( hitBrick )
                {
                    m_score++;
                    if (m_score == m_bricks.length()-1){ //сбили все кирпичи
                        m_paused = true; //останавливаем игру
                        mBall->stop();

                    }
                    brickRect = hitBrick->sceneBoundingRect();
                    hitBrick->destroy();
                    QString score = QString::number(m_score);
                    scores->setText(score);
                }
            if( time == oldTime )
                mBall->stop();  // Protection against balls of exactly same size as the brick height
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
