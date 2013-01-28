#include "myscene.h"

MyScene::MyScene(QObject *parent) :
    QGraphicsScene(parent)
{
}
void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{


    customMouseMoveEvent(event->scenePos().x(), event->scenePos().y());
    QGraphicsScene::mouseMoveEvent(event);
}
