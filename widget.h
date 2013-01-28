#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include "myscene.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    //void mouseMoveEvent(QMouseEvent *);
//signals:
   // void customMouseMoveEvent(int x, int y);
private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_textChanged(const QString &arg1);



    void on_pushButton_Save_clicked();

    void showCursorInfo(int x, int y);


    void on_pushButton_About_clicked();

private:
    Ui::Widget *ui;
    MyScene **sceneArray;
    QGraphicsPixmapItem **itemArray;
    QImage** imgArray;
    int sceneNum;

    int m_width;
    int m_height;
    int m_curIndex;
};

#endif // WIDGET_H
