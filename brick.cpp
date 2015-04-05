#include "brick.h"

brick::brick(int aX, int aY, QColor aColor):
    QGraphicsRectItem( -Width/2, -Height/2, Width, Height), m_color(aColor), m_destroyed(false)
{
    setPos( aX, aY);
    setPen( QPen(Qt::black) );
    setBrush( aColor );
}

void brick::destroy()
{
    m_destroyed = true;
    hide();
}
