#ifndef PATTERNSTORE_H
#define PATTERNSTORE_H
#pragma once

#include <vector>
#include <QMainWindow>

#endif // PATTERNSTORE_H

typedef struct storetext
{
    QString text;   //文本内容
    int radius;   //文本半径
    int font_size;   //文本字体大小
    int angle;   //文本旋转角度

}storetext;


typedef struct recttext
{
    int length;    //矩阵的长
    int width;     //矩阵的宽
    int radius;   //矩阵半径
    int angle;   //文本旋转角度
}recttext;

class patternstore
{
public:
    std::vector<storetext> p_text;
};
