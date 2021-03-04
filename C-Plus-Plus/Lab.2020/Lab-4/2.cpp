/**
 * @file    2.cpp
 * @create  2020/03/18
 * @encoding GBK
 * @author  Holger
 * @description
 * 实验四 函数
 *  编写函数InverseBits。
 *  函数原型要求：	int InverseBits(int Num);
 *  函数功能：		将一个整数的各位数字对调。
 *  main函数功能：	编写测试代码，输入整数和输出新的整数。
 *  示例：			输入123，调用该函数之后，得到结果为321
 */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int InverseBits(int Num);

int main() {
    int number;
    cout << "请输入一个整数：";
    cin >> number;
    int newNumber = InverseBits(number);    //各位数字对调的数字
    cout << "各位数字对调后为：" << newNumber << endl;
    return 0;
}

/*==========================
将一个整数的各位数字对调
参数说明：
	Num:原整数
返回值说明：
	各位数字对调后的整数
==========================*/
int InverseBits(int Num) {
    bool flag = false;    //负数标记
    if (Num < 0) {
        flag = true;
        Num = -Num;        //取绝对值
    }
    vector<int> bits;    //Num从低位到高位的各位数字
    do {
        bits.push_back(Num % 10);
    } while (Num /= 10);
    int result = 0;        //对调结果数字
    for (int i = 0; i < bits.size(); i++) {
        result += int(bits[i] * pow(10, bits.size() - 1 - i));
    }
    return (flag ? -result : result);
}
