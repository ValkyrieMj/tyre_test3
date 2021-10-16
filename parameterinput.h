#ifndef PARAMETERINPUT_H
#define PARAMETERINPUT_H

#include <QMainWindow>
#include <draw_pix.h>
#include "PatternStore.h"

namespace Ui {
class ParameterInput;
}

class ParameterInput : public QMainWindow
{
    Q_OBJECT

public:
    explicit ParameterInput(QWidget *parent = nullptr);
    ~ParameterInput();

    void receive_message(patternstore all_store);

    patternstore p_all_store;
    QString P_text;
    int radius;
    int font_size;
    int angle;

private slots:
    void on_pushButton_clicked();

private:
    Ui::ParameterInput *ui;
};

#endif // PARAMETERINPUT_H
