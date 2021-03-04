//date.cpp
#include "date.h"
#include <iostream>
#include <stdexcept>
using namespace std;

namespace{      //下面的定义仅在本文件中有效
    //储存平年中某月一日前有多少天
    const int DAYS_BEFORE_MONTH[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
}

//Date类方法实现
//构造函数
Date::Date(int year, int month, int day): year(year), month(month), day(day){
    if (day <= 0 || day > getMaxDay())       //不合法的日期判断
        throw runtime_error("Invalid date");
    int years = year-1;
    totalDays = 365*years + years/4 - years/100 + years/400
                + day + DAYS_BEFORE_MONTH[month-1];
    if (isLeapYear() && month > 2)   totalDays++;
}
//获得当月多少天
int Date::getMaxDay() const{
    if (month == 2 && isLeapYear())
        return 29;
    else
        return DAYS_BEFORE_MONTH[month] - DAYS_BEFORE_MONTH[month-1];
}

//全局函数实现
//Date类用于输入和显示日期的全局函数
istream &operator>>(istream &in, Date &date) {
    int year, month, day;
    char c1, c2;
    in >> year >> c1 >> month >> c2 >> day;
    if (c1 != '-' || c2 != '-')     //不合法日期判断
        throw runtime_error("Invalid date");
    date = Date(year, month, day);
    return in;
}
ostream &operator<<(ostream &out, const Date &date){
    out << date.getYear() << '-' << date.getMonth() << '-' << date.getDay();
    return out;
}
