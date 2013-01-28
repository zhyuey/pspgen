#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneEvent>

class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MyScene(QObject *parent = 0);
    
signals:
     void customMouseMoveEvent(int x,int y);
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
public slots:
    
};

#endif // MYSCENE_H
