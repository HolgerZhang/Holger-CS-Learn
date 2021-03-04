/**
 * @file    E02.cpp
 * @create  2020/03/07
 * @encoding GBK
 * @author  Holger
 * @description 求 Sn = a + aa + ... + aa...a 的值。其中a是一个数字。a和n都是由键盘输入。
 *  例如：求  S = 2 + 22 + 222 + 2222 + 22222 + 222222，那么a = 2且n = 6。
 */
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int a, n;
    cout << "请输入a=";
    cin >> a;
    cout << "请输入n=";
    cin >> n;
    if (n < 0) {    //判断n是否合法
        cout << "n不能为0" << endl;
        return 0;
    }
    long sum = 0;        //保存总和
    for (int i = 0; i < n; i++) {
        long each = 0;   //保存an
        for (int j = 0; j <= i; j++) {  //计算an
            each += a * pow(10, j);
        }
        sum += each;     //累加到sun上
    }
    cout << "S=" << sum << endl;
    return 0;
}