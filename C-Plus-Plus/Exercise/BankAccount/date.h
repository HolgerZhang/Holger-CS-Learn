//date.h
#ifndef __DATE_H
#define __DATE_H

#include <iostream>

class Date{             //日期类
private:
    int year;           //年
    int month;          //月
    int day;            //日
    int totalDays;      //自公元元年1月1日的第几天
public:
    Date(int year=1, int month=1, int day=1);     //构造函数
    //私有数据的公有接口
    int getYear() const { return year;}
    int getMonth() const { return month;}
    int getDay() const { return day;}
    int getMaxDay() const;                      //获得当月多少天
    bool isLeapYear() const{                    //判断闰年
        return (year%4==0 && year%100!=0) || year%400==0;
    }
    int operator-(Date date) const{             //计算日期间隔多少天, 重载-运算符
        return totalDays - date.totalDays;
    }
    bool operator<(const Date& date) const {    //判断两个日期的前后差异
        return totalDays < date.totalDays;
    }
};

//Date类用于输入和显示日期的全局函数
std::istream &operator>>(std::istream &in, Date &date);
std::ostream &operator<<(std::ostream &out, const Date &date);


#endif //__DATE_H
