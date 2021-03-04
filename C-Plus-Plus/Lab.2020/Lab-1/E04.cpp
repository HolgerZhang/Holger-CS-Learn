/**
 * @file    E04.cpp
 * @create  2020/03/03
 * @encoding GBK
 * @author  Holger
 * @description
 *  一只大象口渴了，要喝20升水才能解渴，但现在只有一个深h厘米，底面半径为r厘米的小圆桶(h和r都是整数)。
 *  问大象至少要喝多少桶水才会解渴。（注：小圆桶的深h和底面半径r请用户输入，单位默认是厘米。）
 */
#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.14159;	//圆周率

int main()
{
	int h, r;
	//输入小圆桶的深h和底面半径r
	cout << "小圆桶的深h=";	cin >> h;
	cout << "底面半径r=";		cin >> r;
	//计算桶数并输出
	int num = ceil(20000 / (PI * h * r * r));
	cout << "大象至少要喝" << num << "桶水才会解渴" << endl;
	return 0;
}