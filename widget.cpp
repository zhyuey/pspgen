#include "widget.h"
#include "ui_widget.h"

#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QMouseEvent>
#include <QMessageBox>
#include <QIcon>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    sceneNum = 0;
    sceneArray = NULL;
    itemArray = NULL;
    ui->setupUi(this);

    //connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    //connect(ui->view, SIGNAL())
    //connect((MyScene *)ui->view->scene(), SIGNAL(mouseMoveEvent(QMouseEvent *)), this, SLOT(showCursorInfo(QMouseEvent *)));
    ui->view->setMouseTracking(true);
    ui->radioButton_HorizontalFringe->setChecked(true);
    setWindowTitle("Phase Shifting Pattern Generator");
    setFixedSize(800, 600);
    setWindowIcon(QIcon("6.png"));

    m_width = ui->doubleSpinBox_Width->text().toInt();
    m_height = ui->doubleSpinBox_Height->text().toInt();
    m_curIndex = 0;



}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    if(sceneArray)
    {
        for(int i = 0; i < sceneNum; i++)
        {
            delete imgArray[i];
        }
        delete[] imgArray;

    }
    if(itemArray)
    {
        for(int i = 0; i < sceneNum; i++)
        {
            delete itemArray[i];
        }
        delete[] itemArray;
    }
    if(sceneArray)
    {
        for(int i = 0; i < sceneNum; i++)
        {
            delete sceneArray[i];
        }
        delete[] sceneArray;

    }
    ui->comboBox->setEnabled(false);
    ui->comboBox->clear();
    ui->comboBox->setEnabled(true);

    const float PI = 3.1415926f;
    const float TWOPI = PI * 2;

    m_width = ui->doubleSpinBox_Width->text().toInt();
    m_height = ui->doubleSpinBox_Height->text().toInt();

    int width = m_width;
    int height = m_height;


    int period = ui->doubleSpinBox_Period->text().toInt();
    int number = ui->doubleSpinBox_Number->text().toInt();

    sceneNum = number;


    imgArray = new QImage*[number];

    sceneArray = new MyScene*[number];
    itemArray = new QGraphicsPixmapItem*[number];


    for(int i = 0; i < number; i++)
    {
        sceneArray[i] = new MyScene();
        itemArray[i] = new QGraphicsPixmapItem();
        imgArray[i] = new QImage(width, height, QImage::Format_RGB32);
        //item = new QGraphicsPixmapItem();
        QRgb value;
        int tmp;
        if(ui->radioButton_HorizontalFringe->isChecked() == true)
        {
            int row_per_period = height / period;
            for(int h = 0; h < height; h++)
            {
                tmp = (int)(uchar)((cos((float)h/row_per_period * TWOPI - PI + TWOPI / number * i)) * 127.5 + 127.5);
                value = qRgb(tmp, tmp, tmp);
                for(int w = 0; w < width; w++)
                {
                    imgArray[i]->setPixel(w, h, value);
                }
            }
        }
        else
        {
            int col_per_period = width / period;
            for(int w = 0; w < width; w++)
            {
                tmp = (int)(uchar)((cos((float)w / col_per_period * TWOPI - PI + TWOPI / number * i)) * 127.5 + 127.5);
                value = qRgb(tmp, tmp, tmp);
                for(int h = 0; h < height; h++)
                {
                    imgArray[i]->setPixel(w, h, value);
                }
            }

        }
        QPixmap map;
        map.convertFromImage(*imgArray[i], Qt::MonoOnly);
        itemArray[i]->setPixmap(map);
        sceneArray[i]->addItem(itemArray[i]);
        //delete imgarray[i];
        //imgarray[i];
        QString cc;
        cc.setNum(i);
        ui->comboBox->addItem(cc);
    }
    m_curIndex = 0;
    ui->view->setScene(sceneArray[0]);
    ui->view->update();
    ui->view->show();
    connect(sceneArray[0], SIGNAL(customMouseMoveEvent(int,int)), this, SLOT(showCursorInfo(int, int)));
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    if(ui->comboBox->isEnabled() && sceneArray && index < sceneNum && sceneArray[index])
    {
        disconnect(sceneArray[m_curIndex], SIGNAL(customMouseMoveEvent(int,int)), this, SLOT(showCursorInfo(int, int)));
        ui->view->setScene(sceneArray[index]);
        ui->view->update();
        connect(sceneArray[index], SIGNAL(customMouseMoveEvent(int,int)), this, SLOT(showCursorInfo(int, int)));

        m_curIndex = index;
    }
}

void Widget::on_comboBox_textChanged(const QString &arg1)
{

}



void Widget::on_pushButton_Save_clicked()
{
    if(!imgArray || !sceneArray || !itemArray)
    {
        QMessageBox::critical(NULL, "Error", "Please generate images first!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;

    }
    QFileDialog* openFilePath = new QFileDialog(this, "Please choose a folder", "");
    openFilePath->setFileMode(QFileDialog::DirectoryOnly);
    if(openFilePath->exec() == QDialog::Accepted)
    {
        QString dir = openFilePath->selectedFiles()[0];
        //ui->info->setText(dir);
        for(int i = 0; i < sceneNum; i++)
        {
            QString fn;
            fn = dir + "/pattern_" + QString::number(i) +".bmp";

            if(!itemArray[i] || !(itemArray[i]->pixmap().save(fn)))
            {
                QMessageBox::critical(NULL, "Error", "Could not save image to " + fn);
                return;
            }

        }
        QMessageBox::information(NULL, "Congratulation", "The patterns have been saved successfully!");
    }
}
void Widget::showCursorInfo(int x, int y)
{
    if(x < 0)
        x = 0;
    else if(x >=m_width)
        x = m_width - 1;
    if(y < 0)
        y = 0;
    else if(y >= m_height)
        y = m_height - 1;


    QString str1 = "X: " + QString::number(x) + " Y: " + QString::number(y);
    int index = ui->comboBox->currentIndex();
    int stride = imgArray[index]->bytesPerLine();
    int loc = y * stride + x * 4;
    int content = (int)(imgArray[index]->bits()[loc]);
    QString str2 = " Index: " + QString::number(content);
    //QString str2 = "GrayScale: " + QString.number((int)imgArray[i]->bits()[(y * 768 + x) * 4]);
    ui->info->setText(str1 + str2);
}

void Widget::on_pushButton_About_clicked()
{
   // QMessageBox::about(NULL, "About", "Phase Shifting Pattern Generator\nVersion: 0.1.0\nWritten by Yueyi Zhang\nJan. 4th 2013");
    QMessageBox* qboxAbout = new QMessageBox();
    qboxAbout->setIcon(QMessageBox::Information);
    qboxAbout->setWindowTitle("About");
    qboxAbout->setText("Phase Shifting Pattern Generator\nVersion: 0.1.0\nWritten by Yueyi Zhang\nJan. 4th 2013");
    qboxAbout->exec();

}
