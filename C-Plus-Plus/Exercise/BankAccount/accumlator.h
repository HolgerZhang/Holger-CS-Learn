//accumlator.h
#ifndef __ACCUMLATOR_H
#define __ACCUMLATOR_H

#include "date.h"

class Accumlator{           //将某个数值按日累加类
private:
    Date lastDate;          //上次数值变更日期
    double value;           //当前数值
    double sum;             //数值按日累加和
public:
    //构造函数, date为开始日期, value为初始值
    Accumlator(const Date& date, double value)
        :lastDate(date), value(value), sum(0){ }
    //获得到日期date的累加结果
    double getSum(const Date& date) const {
        return sum + value*(date-lastDate);
    }
    //在日期date将当前数值value变为new_value
    void change(const Date& date, double new_value){
        sum = getSum(date);
        lastDate = date;
        this->value = new_value;
    }
    //重置(初始化), 日期变为date, 当前数值变为value, 累加器置为0
    void reset(const Date& date, double new_value){
        lastDate = date;
        this->value = new_value;
        sum = 0;
    }
};

#endif //__ACCUMLATOR_H
