/**
 * @file    4.cpp
 * @create  2020/03/18
 * @encoding GBK
 * @author  Holger
 * @description
 * 实验四 函数
 *  编写三个重载函数printOut分别实现输出整型数、浮点型数和string字符串
 *  要求如下：
 *      - 整型数：占10列，右对齐
 *      - 浮点型：有4位小数
 *      - 字符串：占10列，右对齐
 *  main函数：编写测试程序，测试程序中的整数、浮点数和字符串由用户输入
 */
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void printOut(int num);

void printOut(double num);

void printOut(const string &str);

int main() {
    //测试浮点数
    double numberDouble;
    cout << "请输入一个浮点数：";
    cin >> numberDouble;
    printOut(numberDouble);
    cout << endl;

    //测试整型数
    int numberInt;
    cout << "请输入一个整型数：";
    cin >> numberInt;
    printOut(numberInt);
    cout << endl;

    //测试字符串
    string str;
    cout << "请输入一个字符串：";
    cin >> str;
    printOut(str);
    cout << endl;

    return 0;
}

/*=================================
输出整型数，占10列，右对齐
参数说明：
	num:要输出的整型数
返回值说明：
	无返回值
=================================*/
void printOut(int num) {
    cout << setw(10) << num;
}

/*=================================
输出浮点数，有4位小数
参数说明：
	num:要输出的浮点数
返回值说明：
	无返回值
=================================*/
void printOut(double num) {
    cout << setiosflags(ios_base::fixed);
    cout << setprecision(4) << num;
    cout << resetiosflags(ios_base::fixed);    //恢复cout状态
}

/*=================================
输出字符串，占10列，右对齐
参数说明：
	str:要输出的字符串的常引用
返回值说明：
	无返回值
=================================*/
void printOut(const string &str) {
    cout << setw(10) << str;
}
