#include "draw_pix.h"
#include "canvas.h"
#include <QPainter>
#include <QDebug>
#include <QPushButton>
#include <qmath.h>

draw_pix::draw_pix(QWidget *parent) : QWidget(parent)
{
    qDebug()<<"flag";
    qDebug()<<flag;
//    QPushButton * btn = new QPushButton("不要按",this);
//    connect(btn,&QPushButton::clicked,[=](){
//        qDebug()<<"打印";
//        updaTextPixmap();
//        update();
//    });
    //updaTextPixmap();
}



void draw_pix::updaTextPixmap(patternstore all_store)
{
//    QPixmap pixmap(this->width(),this->height());
//    //pixmap.fill(Qt::transparent);
//    pixmap.fill(Qt::white);
//    QString content = m_text;
//    qreal q = m_angle;  //旋转角度
//    QPainter painter(&pixmap);
//    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::HighQualityAntialiasing | QPainter::SmoothPixmapTransform);
//    painter.setPen(QPen(QColor("#FEA47F"), 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
//    painter.setBrush(Qt::NoBrush);
//    QFont font = painter.font();
//    font.setFamily("Microsoft YaHei");
//    font.setPointSize(m_fontsize);   //设置字体大小
//    font.setWeight(60);
//    painter.setFont(font);

//    qreal xoffset = painter.fontMetrics().height();
//    qreal yoffset = xoffset;
//    qreal a = this->width() / 2.0 - xoffset;
//    qreal b = this->height() / 2.0 - yoffset;

////    qDebug()<<painter.fontMetrics().height();
//    painter.translate(xoffset, yoffset);
//    painter.translate(a, b);
////    qDebug()<<a;
////    qDebug()<<b;
////    painter.translate(this->width()/2,this->height()/2);
//    painter.rotate(120);

//    for(int i = 0; i < content.length(); i++)
//    {
//        qreal xpos = 0;
//        qreal ypos = 0;

//        if( q == 90 || q == 270)
//        {
//            xpos = 0;
//            ypos = -b;
//        }
//        else
//        {
//            xpos = 0;
//            qreal angle = q * M_PI * 1.0 / 180;
//            qreal tanValue = qTan(angle) * qTan(angle);
//            qreal tmp = (1 + tanValue) * 1.0 / (qPow(b, 2) + qPow(a, 2) * tanValue);
//            ypos = 0 - a * b * qSqrt(tmp);
//        }

//        painter.save();
//        painter.rotate(q);
//        const QChar && charTxt = content.at(i);
//        qreal l = painter.fontMetrics().width(charTxt) /1.0;  //调整字间距
//        painter.drawText(QPointF(xpos - l, ypos+m_radius), charTxt);  //ypos可以调整半径
//        //painter.drawText(QPointF(100,100), charTxt);
//        //qDebug()<<QPointF(xpos - l, ypos);
//        painter.restore();
//        q = q + (l * 360.0) / (M_PI * qAbs(ypos)) + 3;
//        //qDebug()<<l;
//    }

//    painter.drawEllipse(QPoint(0,0),150,150);
//    m_pixmap = pixmap;
//    update();
//    for(int i = 0;i<all_store.p_text.size();i++)
//        qDebug()<<all_store.p_text[i].text;





    QPixmap pixmap(this->width(),this->height());
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    painter.translate(this->width()/2,this->height()/2);
    for(int j = 0;j<all_store.p_text.size();j++)
    {
        QString content = all_store.p_text[j].text;
        qreal q = all_store.p_text[j].angle;  //旋转角度
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::HighQualityAntialiasing | QPainter::SmoothPixmapTransform);
        painter.setPen(QPen(QColor("#FEA47F"), 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.setBrush(Qt::NoBrush);
        QFont font = painter.font();
        font.setFamily("Microsoft YaHei");
        font.setPointSize(all_store.p_text[j].font_size);   //设置字体大小
        font.setWeight(60);
        painter.setFont(font);

        qreal xoffset = painter.fontMetrics().height();
        qreal yoffset = xoffset;
        qreal a = this->width() / 2.0 - xoffset;
        qreal b = this->height() / 2.0 - yoffset;
        //painter.translate(this->width()/2,this->height()/2);
        painter.rotate(120);

        for(int i = 0; i < content.length(); i++)
        {
            qreal xpos = 0;
            qreal ypos = 0;

            if( q == 90 || q == 270)
            {
                xpos = 0;
                ypos = -b;
            }
            else
            {
                xpos = 0;
                qreal angle = q * M_PI * 1.0 / 180;
                qreal tanValue = qTan(angle) * qTan(angle);
                qreal tmp = (1 + tanValue) * 1.0 / (qPow(b, 2) + qPow(a, 2) * tanValue);
                ypos = 0 - a * b * qSqrt(tmp);
            }

            painter.save();
            painter.rotate(q);
            const QChar && charTxt = content.at(i);
            qreal l = painter.fontMetrics().width(charTxt) /1.0;  //调整字间距
            //painter.drawText(QPointF(xpos - l, ypos+m_radius), charTxt);  //ypos可以调整半径
            painter.drawText(QPointF(xpos - l, ypos+all_store.p_text[j].radius), charTxt);  //ypos可以调整半径
            painter.restore();
            q = q + (l * 360.0) / (M_PI * qAbs(ypos)) + 3;
        }
    }

    painter.drawEllipse(QPoint(0,0),150,150);
    m_pixmap = pixmap;
    update();
    for(int i = 0;i<all_store.p_text.size();i++)
        qDebug()<<all_store.p_text[i].text;
}

void draw_pix::paintEvent(QPaintEvent *e)
{
    qDebug()<<"画图1";
    QWidget::paintEvent(e);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    //    const qreal iw = m_pixmap.width();
    //    const qreal ih = m_pixmap.height();
    //    const qreal wh = height();
    //    const qreal ww = width();

    //    qDebug()<<ww;
    //    qDebug()<<wh;
    //    qDebug()<<iw;
    //    qDebug()<<ih;
    //    painter.translate(ww / 2, wh / 2);  //整个图形在旋转
    //    painter.rotate(170);
    //    painter.translate(-iw / 2, -ih / 2);
    painter.drawPixmap(0, 0, m_pixmap);
    //    QWidget::paintEvent(e);
    //    QPainter painter(&m_pixmap);
    //    painter.drawPixmap(0,0,m_canvas_pixmap);
}



void draw_pix::setDrawTextonArcPath(const QString& text,const int radius,const int fontsize,const int angle,patternstore all_store)
{
    m_text = text;
    m_radius = radius;
    m_fontsize = fontsize;
    //m_angle = 130;
    m_angle = angle;
    updaTextPixmap(all_store);
}

void draw_pix::Setcanvas_pixmap(const QPixmap& canvas_pixmap)
{
    m_canvas_pixmap = canvas_pixmap;
    flag = 1;
    qDebug()<<"flag";
    qDebug()<<flag;
    qDebug()<<"画图0";
    //updaTextPixmap();
    update();
}
