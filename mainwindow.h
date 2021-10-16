#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <canvas.h>
#include <parameterinput.h>
#include "PatternStore.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void show_pix(QString text,int radiu,int font_size,int angle);
    void m_receive_message(patternstore p_all_store);


    patternstore all_store;

private:
    Ui::MainWindow *ui;
    QString M_text;



protected:
    void paintEvent(QPaintEvent *e);
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
