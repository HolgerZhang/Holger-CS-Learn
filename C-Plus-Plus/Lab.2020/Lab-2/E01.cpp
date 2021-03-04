/**
 * @file    E01.cpp
 * @create  2020/03/07
 * @encoding GBK
 * @author  Holger
 * @description 编写程序打印出ASCII码从32－126的ASCII字符（每行打印5个）。
 */
#include <iostream>

using namespace std;

int main() {
    char ch;    //字符
    int i;        //累计打印的字符数
    //打印出ASCII码从32－126的ASCII字符
    for (ch = 32, i = 1; ch <= 126; ++ch, ++i) {
        cout << ch;
        if (i % 5 == 0)    //每行打印5个
            cout << endl;
    }
    return 0;
}