#include "parameterinput.h"
#include "ui_parameterinput.h"
#include "mainwindow.h"


ParameterInput::ParameterInput(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ParameterInput)
{
    ui->setupUi(this);

    P_text = ui->textEdit->toPlainText();

    void(QSpinBox::*spSignal1)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBox,spSignal1,ui->horizontalSlider,&QSlider::setValue);
    connect(ui->horizontalSlider, &QSlider::valueChanged, ui->spinBox, &QSpinBox::setValue);

    void(QSpinBox::*spSignal2)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBox_2,spSignal2,ui->horizontalSlider_2,&QSlider::setValue);
    connect(ui->horizontalSlider_2, &QSlider::valueChanged, ui->spinBox_2, &QSpinBox::setValue);

    void(QSpinBox::*spSignal3)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBox_3,spSignal3,ui->horizontalSlider_3,&QSlider::setValue);
    connect(ui->horizontalSlider_3, &QSlider::valueChanged, ui->spinBox_3, &QSpinBox::setValue);


}

ParameterInput::~ParameterInput()
{
    delete ui;
}



void ParameterInput::on_pushButton_clicked()
{
//    draw_pix *p = new draw_pix();
//    P_text = ui->textEdit->toPlainText();
//    p->setDrawTextonArcPath(P_text);

//    p->show();
    MainWindow *p = new MainWindow();
    P_text = ui->textEdit->toPlainText();
    radius = ui->spinBox->value()+100;
    font_size = ui->spinBox_2->value()/5;
    angle = ui->spinBox_3->value();

    storetext temp_text = {P_text,radius,font_size,angle};
    p_all_store.p_text.push_back(temp_text);

    p->m_receive_message(p_all_store);
    p->show_pix(P_text,radius+100,font_size/5,angle);
    p->show();
    close();
}

void ParameterInput::receive_message(patternstore main_all_store)  //接收
{
    p_all_store = main_all_store;
}

