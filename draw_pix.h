#ifndef DRAW_PIX_H
#define DRAW_PIX_H

#include <QWidget>
#include "PatternStore.h"

class draw_pix : public QWidget
{
    Q_OBJECT
public:
    explicit draw_pix(QWidget *parent = nullptr);

    void updaTextPixmap(patternstore all_store);
    void paintEvent(QPaintEvent *e);
    void setDrawTextonArcPath(const QString& text,const int radius,const int fontsize,const int angle,patternstore all_store);

    void Setcanvas_pixmap(const QPixmap &canvas_pixmap);

signals:

public slots:


private:
    int flag = 0;
    QPixmap m_pixmap;			// 弧形图像
    QString m_text;				// 弧形文本
    QPixmap m_canvas_pixmap;     //画布的图案

    int m_radius;    //弧形半径
    int m_fontsize = 12;  //文本字体大小
    int m_angle;    //文本旋转角度

};

#endif // DRAW_PIX_H
