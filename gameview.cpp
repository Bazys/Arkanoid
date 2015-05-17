#include "gameview.h"
#include <QGLWidget>

GameView::GameView(QGraphicsScene* scene, QWidget* parent) :
    QGraphicsView(scene, parent)
{
    setAttribute( Qt::WA_DeleteOnClose );

}

void GameView::resizeEvent( QResizeEvent* )
{
    fitInView( scene()->sceneRect(), Qt::KeepAspectRatio );
}

void GameView::closeEvent( QCloseEvent* )
{
//    GameScene::instance()->cleanup();
}
