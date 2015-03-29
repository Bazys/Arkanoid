#include "gamescene.h"
#include "gameview.h"
#include <QtWidgets>
#include <QGLWidget>
#include <QApplication>
#include <QObject>

class GameView;
class GameScene;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    GameScene* m_scene = new GameScene;
    GameView* m_view = new GameView( m_scene );
    m_view->setViewport( new QWidget(m_view) );
    m_view->setScene( m_scene );
    m_view->setMouseTracking(true);
    m_view->setCursor( QCursor(Qt::BlankCursor) );
    m_scene->setup();
    m_view->setRenderHint(QPainter::Antialiasing);
    m_view->showNormal();


    QTimer timer;
    timer.start(1000 / 33);

    return a.exec();
}
