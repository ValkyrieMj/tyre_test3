#include "canvas.h"
#include "ui_canvas.h"
#include "draw_pix.h"

#include <QToolBar>
#include <QAction>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QPainterPath>

canvas::canvas(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::canvas)
{
    ui->setupUi(this);
    //this->setGeometry(350,200,600,400);//设置窗体大小、位置
    setMouseTracking(true);//开启鼠标实时追踪，监听鼠标移动事件，默认只有按下时才监听
    //this->setStyleSheet("background-color:white;");
    // 窗口大小设置为600*500
    resize(1000, 1000);
    // 画布大小为200*200，背景为白色
    pix = QPixmap(1000, 500);
    pix.fill(Qt::white);

     //创建工具栏
     QToolBar *tbar = addToolBar(tr("yes"));
     tbar->setMovable(false);//工具栏不可移动
     tbar->setIconSize(QSize(16, 16));//设置动作图标的尺寸
     tbar->setStyleSheet("background-color:rgb(199,237,204)");//背景色


     QAction *linesAction = new QAction(tr("&pencil"), this);//铅笔动作
     linesAction->setShortcut(QKeySequence(tr("Ctrl+P")));//热键
     tbar->addAction(linesAction);//添加到工具栏

     QAction *rectAction = new QAction(tr("&rect"), this);//矩形动作
     rectAction->setShortcut(QKeySequence(tr("Ctrl+R")));//热键
     tbar->addAction(rectAction);

     QAction *ellipseAction = new QAction(tr("&ellipse"), this);//椭圆动作
     ellipseAction->setShortcut(QKeySequence(tr("Ctrl+E")));//热键
     tbar->addAction(ellipseAction);

     QAction *eraserAction = new QAction(tr("&eraser"), this);//橡皮擦动作
     //eraserAction->setShortcut(QKeySequence(tr("Ctrl+E")));//热键
     tbar->addAction(eraserAction);

     QAction *lineAction = new QAction(tr("&line"), this);//直线动作
    // eraserAction->setShortcut(QKeySequence(tr("Ctrl+E")));//热键
     tbar->addAction(lineAction);

     QAction *curveAction = new QAction(tr("&curve"), this);//曲线动作
     tbar->addAction(curveAction);

     QAction *saveAction = new QAction(tr("&save"), this);//保存动作
     tbar->addAction(saveAction);

     connect(linesAction, &QAction::triggered,[=](){
         drawing = 2;  //待机
         drawtype = 1;
     });
     connect(rectAction, &QAction::triggered, [=](){
         drawing = 2;  //待机
          drawtype = 2;
     });
     connect(ellipseAction, &QAction::triggered, [=](){
         drawing = 2;  //待机
         drawtype = 3;
     });

     connect(eraserAction, &QAction::triggered, [=](){
         drawing = 2;  //待机
         drawtype = 4;
     });

     connect(lineAction, &QAction::triggered, [=](){
         drawing = 2;  //待机
         drawtype = 5;   //直线
     });

     connect(curveAction, &QAction::triggered, [=](){
         drawing = 2;  //待机
         drawtype = 6;   //曲线
         qDebug()<<"曲线";
     });

     connect(saveAction, &QAction::triggered, [=](){
         draw_pix A;
        // A.Setcanvas_pixmap(pix);
         close();
         qDebug()<<"关闭";
     });
}

canvas::~canvas()
{
    delete ui;
}

void canvas::paintEvent(QPaintEvent *)
{

    if(drawtype == 1)
    {
        // 根据鼠标指针前后两个位置绘制直线
        QPainter painter(this);
        if(drawing == 1)
        {
            QPainter pp(&pix);
            pp.setRenderHint(QPainter::Antialiasing);
            pp.drawLine(lastPoint, endPoint);
            // 让前一个坐标值等于后一个坐标值，
            // 这样就能实现画出连续的线
            lastPoint = endPoint;
            painter.drawPixmap(0, 0, pix);
        }
        painter.drawPixmap(0, 0, pix);

    }
    else if(drawtype == 2)
    {
        int x = lastPoint.x();
        int y = lastPoint.y();
        int w = endPoint.x()-x;
        int h = endPoint.y()-y;

        QPainter painter(this);
        if(drawing == 1)
        {
            tmp_pix=pix;
            QPainter pp(&tmp_pix);
            pp.drawRect(QRect(x,y,w,h));
//            painter.drawRect(QRect(x,y,w,h));
            painter.drawPixmap(0, 0, tmp_pix);
        }
        else if(drawing == 0)
        {
            QPainter pp(&pix);
            pp.drawRect(QRect(x,y,w,h));
//            painter.drawRect(QRect(x,y,w,h));
            painter.drawPixmap(0, 0, pix);
        }
    }
    else if(drawtype == 3)
    {
         QPainter painter(this);
         int x = lastPoint.x();
         int y = lastPoint.y();
         int w = endPoint.x()-x;
         int h = endPoint.y()-y;
         if(drawing == 1)
         {
            // qDebug()<<"第一";
             tmp_pix=pix;
             QPainter pp(&tmp_pix);
             pp.drawEllipse( QPoint(x,y) ,w, h);
             painter.drawPixmap(0, 0, tmp_pix);
         }
         else if(drawing == 0) //结束
         {
             //qDebug()<<"椭圆";
                 qDebug()<<lastPoint<<" "<<endPoint<<"椭圆画下";
                 QPainter pp(&pix);
                 pp.drawEllipse( QPoint(x,y) ,w, h);
                 painter.drawPixmap(0, 0, pix);
         }
    }
    else if(drawtype == 4)   //橡皮擦
    {
        QPainter painter(this);
        if(drawing == 1)
        {
            QPainter pp(&pix);
            QPen pen(QColor(255,255,255));
            pen.setWidth(20);
            pp.setPen(pen);
            pp.drawLine(lastPoint, endPoint);
            lastPoint = endPoint;
            painter.drawPixmap(0, 0, pix);
        }
        painter.drawPixmap(0, 0, pix);
    }

    else if(drawtype == 5)
    {
         QPainter painter(this);
         if(drawing == 1)  //正在画
         {
             tmp_pix=pix;
             QPainter pp(&tmp_pix);
             pp.drawLine(tmpoint,endPoint);
             painter.drawPixmap(0, 0, tmp_pix);
         }
         else if(drawing == 0) //结束
         {
                 QPainter pp(&pix);
                 pp.drawLine(tmpoint,endPoint);
                 painter.drawPixmap(0, 0, pix);
         }
    }

    else if(drawtype == 6)
    {
        QPainter painter(this);
        if(drawing == 1 || drawing == 3 || drawing == 4)  //曲线确定首末两点
        {
            tmp_pix=pix;
            QPainter pp(&tmp_pix);

            QPainterPath myPath;
            myPath.moveTo(lastPoint);
            myPath.cubicTo(tmpoint, tmpoint1, endPoint);
            //pp.setPen(Qt::red);
            pp.drawPath(myPath);
            painter.drawPixmap(0, 0, tmp_pix);

        }
        else if(drawing == 0)
        {
            QPainter pp(&pix);
            QPainterPath myPath;
            myPath.moveTo(lastPoint);
            myPath.cubicTo(tmpoint, tmpoint1, endPoint);
            pp.drawPath(myPath);
            painter.drawPixmap(0, 0, pix);
        }
    }
}

void canvas::mousePressEvent(QMouseEvent *event){
        //鼠标左键按下

        if(event->button() == Qt::LeftButton & (drawtype == 1 || drawtype == 2
                || drawtype == 3 || drawtype == 4 || drawtype == 5))
        {
               qDebug()<<"鼠标按下"<<drawtype;
                lastPoint = event->pos();
                endPoint = lastPoint;
                tmpoint = lastPoint;
                qDebug()<<lastPoint<<" "<<endPoint<<"左键按下";
                drawing = 1;
        }

        else if(event->button() == Qt::LeftButton && drawtype == 6)
        {
            if(drawing == 2)
            {
                 lastPoint = event->pos();
                 endPoint = lastPoint;
                 tmpoint = endPoint;
                 tmpoint1 = endPoint;
                 qDebug()<<lastPoint<<" "<<endPoint<<"曲线鼠标按下1";
                 drawing = 1;
            }
            else if(drawing == 3) //确定第一个拐点
            {
                tmpoint = event->pos();
                //drawing = 1;
            }
            else if(drawing == 4) //确定第二个拐点
            {
                tmpoint1 = event->pos();
            }
        }

}

void canvas::mouseMoveEvent(QMouseEvent *event)
{
    // 鼠标左键按下的同时移动鼠标

    if(event->buttons() & Qt::LeftButton & (drawtype == 1 | drawtype == 2
                             | drawtype == 3 | drawtype == 4 | drawtype == 5))
    {
       drawing = 1;
       endPoint = event->pos();
       //qDebug()<<lastPoint<<" "<<endPoint<<"左键移动";
       update();//进行绘制
    }
    else if(event->buttons() && Qt::LeftButton && (drawtype == 6) )
    {
        if(drawing == 1)
        {
            endPoint = event->pos();
            tmpoint = endPoint;
            tmpoint1 = endPoint;
            qDebug()<<lastPoint<<" "<<endPoint<<"左键移动";
            update();//进行绘制
        }
        else if(drawing == 3)  //绘制第一个拐点
        {
            tmpoint = event->pos();
            update();
        }
        else if(drawing == 4)  //绘制第二个拐点
        {
            tmpoint1 = event->pos();
            update();
        }
    }
}

void canvas::mouseReleaseEvent(QMouseEvent *event)
{
        if(event->button() == Qt::LeftButton && (drawtype == 1 | drawtype == 2
                                   | drawtype == 3 | drawtype == 4 | drawtype == 5)) //鼠标左键释放
        {
            endPoint = event->pos();
            drawing = 0;
            qDebug()<<"释放鼠标";
            update();
           // lastPoint = endPoint;

        }
        else if(event->button() == Qt::LeftButton && drawtype == 6)
        {
            if(drawing == 1)
            {
                endPoint = event->pos();
                drawing = 3;   //曲线绘画进入确定第一个拐点
                qDebug()<<"释放鼠标1";
                update();
            }
            else if(drawing == 3)
            {
                tmpoint = event->pos();
                drawing = 4;   //曲线绘画进入确定第二个拐点
                qDebug()<<"释放鼠标2";
                update();
            }
            else if(drawing == 4)  //最后结束
            {
                tmpoint1 = event->pos();
                drawing = 0;
                update();
            }
        }
}


