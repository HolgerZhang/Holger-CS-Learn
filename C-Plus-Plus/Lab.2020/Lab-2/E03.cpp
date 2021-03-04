/**
 * @file    E03.cpp
 * @create  2020/03/07
 * @encoding GBK
 * @author  Holger
 * @description
 *  程序员小明年薪N万，他希望在天赐庄买一套55平米的房子，
 *  现在价格是200万，假设房子价格以每年百分之k增长，并且该程序员未来年薪不变，
 *  且不吃不喝，不用交税，每年所得N万全都积攒起来，问第几年能够买下这套房子？
 *  （N和k请用户输入，N（10 <= N <= 50）, K（1 <= K <= 20）），
 *  如果在第20年之前（含20年）就能买下这套房子，则输出一个整数M，
 *  表示最早需要在第M年能买下，否则输出Impossible。
 */
#include <iostream>

using namespace std;

int main() {
    int N, k;
    cout << "程序员小明的年薪为(10<=N<=50)";
    cin >> N;
    cout << "房子价格每年增长百分之(1<=k<=20)";
    cin >> k;
    if (10 > N || N > 50 || 1 > k || k > 20) {
        //判断N, k是否合法(10 <= N <= 50，1 <= k <= 20）
        cout << "您输入的数据有误" << endl;
        return 0;
    }
    double price = 200.0;    //房子的价格（万）
    int result = -1;        //记录最早需要在第几年能买下
    for (int i = 1; i <= 20; ++i) {    //i为当前年份，仅循环20次
        //房子价格每年增长
        price *= 1 + k / 100.0;
        if (N * i >= price) {        //判断当年能否买下
            result = i;
            break;
        }
    }
    if (result >= 0 && result <= 20)
        cout << "小明最早需要在第" << result << "年能买下" << endl;
    else
        cout << "Impossible" << endl;
    return 0;
}