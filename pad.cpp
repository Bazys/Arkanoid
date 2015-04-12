#include "pad.h"
#include <QPainter>
#include <QLinearGradient>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

const QColor Pad::Color = Qt::darkGreen;

void Pad::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qreal x = event->scenePos().x();
    QRectF sceneRect = scene()->sceneRect();
    if( x >= sceneRect.left() && x <= sceneRect.right() )
        m_mouseX = event->scenePos().x();   // Let's not move the paddle too often
}

void Pad::keyPressEvent(QKeyEvent *event)
{
    switch( event->key())
    {
     case Qt::Key_Left:
        startKeyMove( -1 );
        break;
     case Qt::Key_Right:
        startKeyMove( 1 );
        break;
     case Qt::Key_Space:
        emit pausePressed();
        break;
     default:
        event->ignore();
     }
}

void Pad::keyReleaseEvent(QKeyEvent *event)
{
    switch( event->key())
    {
     case Qt::Key_Left:
     case Qt::Key_Right:
        stopKeyMove();
        break;
     default:
        event->ignore();
     }

}

void Pad::timerEvent(QTimerEvent *aEvent)
{
    if( aEvent->timerId() == m_mouseMoveTimer )
        if( m_mouseX != UndefinedPos )
            setX( m_mouseX );
    if( aEvent->timerId() == m_keyMoveTimer )
        moveWithKey();
}

Pad::Pad(int aX, int aY):QGraphicsRectItem( -Width/2, -Height/2, Width, Height),
    m_keyMoveTimer( -1 ), m_mouseX( UndefinedPos )
{
    setPos( aX, aY);
    QLinearGradient gradient( 0, rect().top(), 0, rect().bottom() );
    gradient.setColorAt( 0, Color );
    gradient.setColorAt( 0.5, Color.lighter( 300 ) );
    gradient.setColorAt( 1, Color );
    setBrush( gradient );
    m_mouseMoveTimer = startTimer( 30 );
}
void Pad::startKeyMove( int aDir )
{
    m_keyMoveDir = aDir;
    m_mouseX = UndefinedPos;
    moveWithKey();
    m_keyMoveTimer = startTimer( 20 );
}

void Pad::moveWithKey()
{
    qreal newX = x() + m_keyMoveDir * KeyMoveSpeed;
    if( scene()->sceneRect().contains( newX, y()) )
        setX( newX );
}

void Pad::stopKeyMove()
{
    if( m_keyMoveTimer >= 0 )
        {
        killTimer( m_keyMoveTimer );
        m_keyMoveTimer = -1;
    }
}

void Pad::paint(QPainter *aPainter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    aPainter->setBrush( brush() );
    aPainter->drawRoundedRect( rect(), 5, 5 );
}
