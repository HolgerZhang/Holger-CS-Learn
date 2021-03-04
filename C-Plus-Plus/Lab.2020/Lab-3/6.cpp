/**
 * @file    6.cpp
 * @create  2020/03/18
 * @encoding GBK
 * @author  Holger
 * @description
 * 实验三 数据类型和数组
 * 编写程序对12个月的英文单词根据字典序进行从小到大的排序，请使用string向量实现。
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    vector<string> months = {    //12个月的英文单词
            "January", "February", "March", "April", "May", "June", "July",
            "August", "September", "October", "November", "December"
    };
    //从小到大排序
    sort(months.begin(), months.end());
    //输出排序结果，每个占10列，每行6个
    for (int i = 0; i < months.size(); i++) {
        cout << setiosflags(ios_base::left);
        cout << setw(10) << months[i];
        if ((i + 1) % 6 == 0) {
            cout << endl;
        }
    }
    return 0;
}