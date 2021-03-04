/**
 * @file    E03.cpp
 * @create  2020/03/03
 * @encoding GBK
 * @author  Holger
 * @description 已知2017年1月1日是星期日，输入2017年的一个月和日，输出该天是星期几。
 */
#include <iostream>

using namespace std;

//枚举表示一周七天
enum WEEK {
    Sun, Mon, Tues, Wed, Thur, Fri, Sat
};
//储存2017年某月1日前有多少天
const int DAYS_BEFORE_MONTH[] = {
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
};

//判断日期是否合法
bool judgeDate(int month, int day) {
    //判断month是否合法
    if (month < 1 || month > 12)
        return false;
    //判断day是否合法
    //DAYS_BEFORE_MONTH[month]-DAYS_BEFORE_MONTH[month-1]表示当月天数
    if (day < 1 || day > DAYS_BEFORE_MONTH[month] - DAYS_BEFORE_MONTH[month - 1])
        return false;
    return true;
}

int main() {
    int month, day;
    for (;;) {
        //读取并判断日期是否合法
        cout << "月：";
        cin >> month;
        cout << "日：";
        cin >> day;
        if (judgeDate(month, day))
            break;
        else
            cout << "输入有误，请重新输入！" << endl;
    }

    //一年中的第几天（从0开始）
    int totalDays = day + DAYS_BEFORE_MONTH[month - 1] - 1;
    //输出星期情况
    cout << "2017年" << month << "月" << day << "日是星期";
    switch (totalDays % 7) {
        case Sun:
            cout << "日" << endl;
            break;
        case Mon:
            cout << "一" << endl;
            break;
        case Tues:
            cout << "二" << endl;
            break;
        case Wed:
            cout << "三" << endl;
            break;
        case Thur:
            cout << "四" << endl;
            break;
        case Fri:
            cout << "五" << endl;
            break;
        case Sat:
            cout << "六" << endl;
            break;
    }

    return 0;
}