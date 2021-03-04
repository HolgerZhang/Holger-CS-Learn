#include "Calcultor.h"
#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

namespace {     //仅本文件有效
    //tool function: 将字符串转为实数
    inline double _double(const string &str){
        istringstream stream(str);      //字符串输入流
        double result;
        stream >> result;
        return result;
    }
}

//计算器类实现
//操作数num入栈
void Calcultor::enter(double num) {
    numbers.push(num);
}
//连续两个操作数出栈并放入opn1, opn2
bool Calcultor::get(double &opn1, double &opn2) {
    if(numbers.empty()){
        cerr << "OperandError: missing operand!" << endl;
        return false;
    }
    opn2 = numbers.pop();   //右操作数
    if(numbers.empty()){
        cerr << "OperandError: missing operand!" << endl;
        return false;
    }
    opn1 = numbers.pop();   //左操作数
    return true;
}

//执行opera制定的运算
void Calcultor::__compute(char opera) {
    double operand1, operand2;
    bool succeed = get(operand1, operand2);
    if(succeed){
        switch (opera){
            case '+': numbers.push(operand1 + operand2); break;
            case '-': numbers.push(operand1 - operand2); break;
            case '*': numbers.push(operand1 * operand2); break;
            case '/':
                if(operand2 == 0){
                    cerr << "DivideZeroError: divided by 0!" << endl;
                    numbers.clear();
                } else
                    numbers.push(operand1 / operand2);
                break;
            case '^': numbers.push(pow(operand1, operand2)); break;
            default: cerr << "OperatorError: unrecognized operator!" << endl;
                break;
        }
        if(!numbers.empty()) cout << "= " << numbers.get() << ' ';   //输出结果
    } else numbers.clear();     //操作数不足 清空栈
}

void Calcultor::run() {
    string str;
    while (cin >> str, str != "q"){
        switch (str[0]){
            case 'c': numbers.clear(); break;
            case '-':
                //判断是减号还是负号
                if(str.size() > 1)
                    enter(_double(str));
                else
                    __compute(str[0]);
                break;
            case '+':
            case '*':
            case '/':
            case '^':
                __compute(str[0]); break;
            default:
                //转换操作数为数字
                enter(_double(str)); break;
        }
    }
}

void Calcultor::clear() {
    numbers.clear();
}

void Calcultor::help() {
    cout << "         CLACULTOR        " << endl
         << "============HELP============" << endl
         << "×支持的运算: " << endl
         << " 加(+)减(-)乘(*)除(/)乘方(^) " << endl
         << "×运算输入格式: " << endl
         << " 数字 数字 运算符" << endl
         << "支持在运算结果的基础上继续运算" << endl
         << "清除历史数据输入 c , 退出输入 q" << endl
         << "----------------------------" << endl;
}
