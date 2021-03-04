/**
 * @file    E02.cpp
 * @create  2020/03/03
 * @encoding GBK
 * @author  Holger
 * @description
 *  从键盘输入一个字母，如果输入的是小写字母，请将其转换为大写字母输出，
 *  如果输入的是大写字母，请将其转换为小写字母输出，其余情况原样输出，请编写程序实现。
 */
#include <iostream>

using namespace std;

int main() {
    char ch;
    //从键盘读取一个字符
    cout << "请输入一个字符：";
    cin >> ch;
    if (ch >= 'A' && ch <= 'Z')
        ch += 32;    //大写字母转小写字母
    else if (ch >= 'a' && ch <= 'z')
        ch -= 32;    //小写字母转大写字母
    //输出转换后的字母
    cout << "转换后的字符为：" << ch << endl;
    return 0;
}