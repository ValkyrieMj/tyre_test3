#ifndef CANVAS_H
#define CANVAS_H

#include <QMainWindow>
#include <QMouseEvent>

namespace Ui {
class canvas;
}

class canvas : public QMainWindow
{
    Q_OBJECT

public:
    explicit canvas(QWidget *parent = nullptr);

    ~canvas();

private:
    Ui::canvas *ui;

    QPixmap pix;
    QPixmap tmp_pix;
    QPoint lastPoint;
    QPoint endPoint;
    QPoint tmpoint;
    QPoint tmpoint1;

    int drawtype;//图形编号
    int drawing;  //0是结束，1是正在画，2是待机

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // CANVAS_H
