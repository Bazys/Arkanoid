#include "brick.h"

Brick::Brick(int aX, int aY, QColor aColor):
    QGraphicsRectItem( -Width/2, -Height/2, Width, Height), m_color(aColor), m_destroyed(false)
{
    setPos( aX, aY);
    setPen( QPen(Qt::black) );
    QLinearGradient gradient( -Height/3, rect().top(), Height/3, rect().bottom() );
    gradient.setColorAt( 0, m_color );
    gradient.setColorAt( 0.5, m_color.light() );
    gradient.setColorAt( 1, m_color );
    setBrush( gradient );
}

void Brick::destroy()
{
    m_destroyed = true;
    hide();
}
