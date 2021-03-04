/**
 * @file    E05.cpp
 * @create  2020/03/07
 * @encoding GBK
 * @author  Holger
 * @description
 *  校长将粉笔作为工资，发放给认真的教师。
 *  第一天，教师收到一支粉笔；
 *  之后两天（第二天和第三天）里，每天收到两支粉笔；
 *  之后三天（第四、五、六天）里，每天收到三支粉笔；
 *  之后四天（第七、八、九、十天）里，每天收到四支粉笔……
 *  这种工资发放模式会一直这样延续下去：
 *  当连续N天每天收到N支粉笔后，教师会在之后的连续N+1天里，每天收到N+1支粉笔（N为任意正整数）。
 *  请编写一个程序，确定从第一天开始的给定n天数内（n<500），教师一共获得了多少粉笔。
 */
#include <iostream>

using namespace std;

int main() {
    int n;
    do {
        cout << "请输入要计算的多少天内教师获得的粉笔：";
        cin >> n;
    } while (n <= 0);
    //num为每天收到的粉笔数量
    //cnt为收到num支粉笔的天数
    //sum为收到的粉笔总数
    unsigned num = 1, cnt = 0, sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += num;        //循环累加
        cnt++;            //天数加一
        if (cnt == num) {    //判断是否连续N天每天收到N支粉笔
            num++;            //粉笔数加一
            cnt = 0;        //天数归零
        }
    }
    cout << "教师一共获得了" << sum << "支粉笔。" << endl;
    return 0;
}