/**
 * @file    1.cpp
 * @create  2020/03/18
 * @encoding GBK
 * @author  Holger
 * @description
 * 实验四 函数
 *  编写函数IsPrime。
 *  函数原型要求：	int IsPrime(int Num);
 *  函数功能：		判断一个整数是否是素数。
 *  main函数功能：	求1000以内的所有质数，每行8个输出到屏幕上。
 */
#include <iostream>
#include <cmath>

using namespace std;

int IsPrime(int Num);

int main() {
    int i, cnt;    //i从2取到1000，cnt统计输出的个数
    for (i = 2, cnt = 0; i <= 1000; i++) {
        if (IsPrime(i)) {
            cout << i << '\t';
            cnt++;
            if (cnt % 8 == 0) {    //每行8个
                cout << endl;
            }
        }
    }
    return 0;
}

/*==========================
判断一个整数是否是素数
参数说明：
	Num:待判断的整数
返回值说明：
	0——Num不是素数；
	1——Num是素数
==========================*/
int IsPrime(int Num) {
    if (Num <= 1) {
        return 0;
    }
    int End = int(sqrt(Num));    //循环终点数据
    for (int i = 2; i <= End; i++) {
        if (Num % i == 0) {
            return 0;
        }
    }
    return 1;
}
