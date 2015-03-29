#ifndef PAD_H
#define PAD_H
#include <QColor>
#include <QPointF>
#include <QSizeF>
#include <QRectF>
#include <QGraphicsRectItem>
#include "gamescene.h"

class QPainter;

class Pad : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    int m_keyMoveTimer;
    int m_keyMoveDir;
    int m_mouseMoveTimer;
    qreal m_mouseX;
protected:
    void mouseMoveEvent( QGraphicsSceneMouseEvent* event );
    void keyPressEvent(QKeyEvent* event );
    void keyReleaseEvent(QKeyEvent* event );
    void timerEvent( QTimerEvent* aEvent );
signals:
    void pausePressed();
public:
    Pad(int aX, int aY);
    enum { Type = GameScene::PadItem };
    int type() const { return Type; }
    void startKeyMove( int aDir );
    void moveWithKey();
    void stopKeyMove();
    void paint( QPainter* aPainter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0 );
    static const int Width = 80;
    static const int Height = 20;
    static const int KeyMoveSpeed = 8;
    static const int UndefinedPos = -10000;
    static const QColor Color;
};

#endif // PAD_H
