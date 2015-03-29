#ifndef GAMEVIEW_H
#define GAMEVIEW_H
#include <QGraphicsView>

class GameView : public QGraphicsView
{
protected:
    void resizeEvent(QResizeEvent* aEvent);
    void closeEvent(QCloseEvent* event);
public:
    explicit GameView(QGraphicsScene* scene, QWidget* parent = 0);
};

#endif // GAMEVIEW_H
