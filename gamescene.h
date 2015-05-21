#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsSvgItem>
#include <math.h>

class ball;
class Pad;
class Brick;
//Класс игровой сцены. На нём рисуются все элементы
class GameScene : public QGraphicsScene
{
    Q_OBJECT
    // группа методов вызываемых из публичного метода setup
    void setupBall();//устанавливаем мяч
    void setupPad();//устанавливаем доску для отбивания
    void setupBricks();// устанавливаем кирпичи
    void setupHearts(int tries);
    void moveBall();//перемещение мяча

    int m_timer;//когда игра запущена
    int m_score; //счетчик очков
    int m_tries; // счетчик попыток
    bool m_paused;//игра на паузе
    bool m_started; // игра стратовала или нет
    ball* mBall; // переменная типа мяч
    Pad* mPad; //переменная типа доска
    QList<Brick*> m_bricks;
    QList<QGraphicsSvgItem*> hearts;
    QGraphicsSimpleTextItem* label;
    QGraphicsSimpleTextItem* scores;
private slots:
    void togglePause(); //событие нажатия на пробел - пауза в игре
protected:
    void timerEvent(QTimerEvent* event); //таймер для событий
    void keyPressEvent(QKeyEvent* event );
    void keyReleaseEvent(QKeyEvent* event );
    void mouseMoveEvent( QGraphicsSceneMouseEvent* event );
public:
    // перечислимый тип для получения информации обо что ударился мяч
    enum
        {
        BrickItem = QGraphicsItem::UserType + 1,
        BallItem,
        PaddleItem,
        ParticleItem
        } ItemTypes;
    GameScene();//конструктор класса
    void setup();//публичный метод настройки мяча, доски и кирпичей
    bool gamePaused() {return m_paused;}
    static const int Width = 800;
    static const int Height = 600;
    static const int BrickRegionTop = -Height/2 + 100;
    static const int BrickRegionBottom = BrickRegionTop + 70;
    static const int GameTick = 1000 / 35 ;    // константа таймера (через какое время перерисовывать) ms
};

#endif // GAMESCENE_H
