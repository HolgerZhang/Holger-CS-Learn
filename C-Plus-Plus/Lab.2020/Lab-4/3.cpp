/**
 * @file    3.cpp
 * @create  2020/03/18
 * @encoding GBK
 * @author  Holger
 * @description
 * 实验四 函数
 *  设计一个函数Calc。
 *  函数原型要求：	void Calc(int Num1, int Num2, int &GCD, int &LCM);
 *  函数功能：
 *          - 接受两个整数作为参数。
 *          - 计算出最大公约数和最小公倍数。（不要在Calc函数中使用输入输出流）
 *          - 可以在函数参数中使用引用。
 *  main函数功能：	测试函数功能。
 */
#include <iostream>

using namespace std;

void Calc(int Num1, int Num2, int &GCD, int &LCM);

int main() {
    int num1, num2;
    cout << "请输入两个整数，用空格分开：";
    cin >> num1 >> num2;
    int GCD = 0, LCM = 0;        //最大公约数和最小公倍数
    Calc(num1, num2, GCD, LCM);    //求解
    cout << "最大公约数：" << GCD << endl;
    cout << "最小公倍数：" << LCM << endl;
    return 0;
}

/*=================================
计算两个整数的最大公约数和最小公倍数
参数说明：
	Num1，Num2:两个整数
	GCD:存放最大公约数的结果
	LCM:存放最小公倍数的结果
返回值说明：
	无实际返回值，结果由GCD和LCM返回
=================================*/
void Calc(int Num1, int Num2, int &GCD, int &LCM) {
    if (Num1 == 0 && Num2 == 0) {
        //两数均为0时，均返回0，防止除零错误
        GCD = 0;
        LCM = 0;
        return;
    }
    int product = Num1 * Num2;    //两数乘积
    //辗转相除法求最大公约数，直到Num2为0为止，Num1为最大公约数
    int temp;
    while (Num2) {
        temp = Num2;
        Num2 = Num1 % Num2;
        Num1 = temp;
    }
    GCD = Num1;
    //最小公倍数=两数乘积除以最大公约数
    LCM = product / GCD;
}
