#ifndef _CALCULTOR_H
#define _CALCULTOR_H

#include "Stack.h"

//计算器类声明
class Calcultor {
private:
    Stack<double> numbers;            //操作数栈
    void enter(double num);     //操作数num入栈
    //连续两个操作数出栈并放入opn1, opn2
    bool get(double &opn1, double &opn2);
    void __compute(char opera); //执行opera制定的运算
public:
    void run();     //程序运行入口
    void clear();   //清空历史记录
    static void help();    //获取帮助
};

#endif //_CALCULTOR_H
