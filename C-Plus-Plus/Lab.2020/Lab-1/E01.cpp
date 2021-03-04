/**
 * @file    E01.cpp
 * @create  2020/03/03
 * @encoding GBK
 * @author  Holger
 * @description
 *  编写程序计算用户输入的3个整数的平均值、和、最大值和最小值，并输出到屏幕上。
 *  输出格式要求平均值占 8列，保留4位小数，左对齐；最大值和最小值占 6列，右对齐。
 */
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int numbers[3];    //三个整数
    int sum = 0;       //三个整数的和
    //从键盘读取数据并求和
    cout << "请输入三个整数，并用空格分开：";
    for (int i = 0; i < 3; ++i) {
        cin >> numbers[i];
        sum += numbers[i];
    }

    //平均值
    double average = (double) sum / 3;
    //最大值
    int bigger = (numbers[0] > numbers[1]) ? numbers[0] : numbers[1];
    int max = (bigger > numbers[2]) ? bigger : numbers[2];
    //最小值
    int smaller = (numbers[0] < numbers[1]) ? numbers[0] : numbers[1];
    int min = (smaller < numbers[2]) ? smaller : numbers[2];

    //输出数据
    //左对齐、定点格式，设置实数保留小数点后四位
    cout << setiosflags(ios_base::left | ios_base::fixed)
         << setprecision(4);
    cout << "平均值：" << setw(8) << average << endl;
    //清除状态左对齐和定点格式，改为右对齐
    cout << setiosflags(ios_base::left | ios_base::fixed)
         << setiosflags(ios_base::right);
    cout << "和：" << setw(6) << sum << endl;
    cout << "最大值：" << setw(6) << max << endl;
    cout << "最小值：" << setw(6) << min << endl;

    return 0;
}
