#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "draw_pix.h"
#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    //ui->widget->setDrawTextonArcPath("伯彭波去吃屎吧，我才是世界唯一的救世主",100,100);
   //ui->widget->setDrawTextonArcPath("哈尔滨工业大学主",100,100,20);


//    connect(ui->pushButton,&QPushButton::clicked,[=](){
//        qDebug()<<"触发";
//        ui->widget->setDrawTextonArcPath("伯彭波去吃屎吧");
//    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    // 背景图
    QPainter p(this);
    p.fillRect(this->rect(), QColor("#182C61"));
}


void MainWindow::on_pushButton_2_clicked()
{
    canvas *Canvas = new canvas();
   // Canvas->setModal(true);
    Canvas->show();
}


void MainWindow::on_pushButton_clicked()
{
    ParameterInput *parameterinput1 = new ParameterInput();
    parameterinput1->receive_message(all_store);
    parameterinput1->show();
    close();
}


//void MainWindow::show_pix(QString text,int radiu,int font_size)
//{
//    M_text = text;
//    ui->widget->setDrawTextonArcPath(M_text,radiu,font_size);
//}

void MainWindow::show_pix(QString text,int radiu,int font_size,int angle)
{
    M_text = text;
   // storetext temp_text = {text,radiu,font_size,angle};
   // all_store.p_text.push_back(temp_text);
    ui->widget->setDrawTextonArcPath(M_text,radiu,font_size,angle,all_store);
}

void MainWindow::m_receive_message(patternstore p_all_store)
{
    all_store = p_all_store;
}
