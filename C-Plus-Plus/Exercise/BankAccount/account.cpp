//account.cpp
#include "account.h"
#include <iostream>
#include <cmath>
#include <utility>
using namespace std;
using namespace rel_ops;


//AccountRecord类实现
//构造函数
AccountRecord::AccountRecord(const Date& date, const Account* account,
        double amount, double balance, const string& desc)
        :date(date), account(account), amount(amount), balance(balance), desc(desc){}
//输出当前记录
void AccountRecord::show() const {
    cout << date << "\t#" << account->getId() << '\t' << amount << '\t'
         << balance << '\t' << desc << endl;
}


//Account类实现
double Account::total = 0;
RecordMap Account::recordMap;
//构造函数
Account::Account(const Date& date, const string& id): id(id), balance(0){
    cout << date << "\t#" << id << " is created." << endl;
    //记录账户当前信息
    pair<Date, AccountRecord> information {
            date,
            AccountRecord(date, this, 0, 0, "Creation")
    };
    recordMap.insert(information);
}
//记账方法
void Account::record(const Date &date, double amount, const string &desc) {
    amount = floor(amount*100+0.5) / 100;     //四舍五入保留小数点后2位(floor为向下取整函数)
    balance += amount; total += amount;
    cout << date << "\t#" << id << "\t" << amount << "\t" << balance <<"\t" << desc << endl;
    //账户记录当前信息
    pair<Date, AccountRecord> information {
        date,
        AccountRecord(date, this, amount, balance, desc)
    };
    recordMap.insert(information);
}
//抛出错误信息的方法
void Account::error(const string& msg) const throw(AccountException) {
    throw AccountException(this, msg);
}
//显示账户信息方法, 虚函数
void Account::show(ostream &out) const {
    out << id << "\tBalance: " << balance;
}
//查询指定日期内的账目记录
void Account::query(const Date &begin, const Date &end) throw(runtime_error) {
    if(begin <= end) {
        RecordMap::iterator iter1 = recordMap.lower_bound(begin);
        RecordMap::iterator iter2 = recordMap.upper_bound(end);
        for (RecordMap::iterator iter=iter1; iter!=iter2; ++iter)
            iter->second.show();
    } else
        throw runtime_error("DateError: begin date should be less than or equal to end date");
}

//Account类及其子类用于输出账户信息的全局函数
inline ostream &operator<<(ostream &out, const Account &account){
    account.show(out);
    return out;
}


//SavingsAccount类方法实现
//构造函数
SavingsAccount::SavingsAccount(const Date& date, const string& id, double rate)
    :Account(date, id), rate(rate), acc(date, 0){ }
//存入方法重写
void SavingsAccount::deposit(const Date& date, double amount, const string& desc) {
    record(date, amount, desc);
    acc.change(date, getBalance());
}
//取出方法重写
void SavingsAccount::withdraw(const Date& date, double amount, const string& desc) {
    if (amount > getBalance())
        error("not enough money");      //余额不足
    else {
        record(date, -amount, desc);
        acc.change(date, getBalance());
    }
}
//计息方法重写(每年1月1日调用)
void SavingsAccount::settle(const Date& date) {
    if (date.getMonth() == 1) {
        double interest = acc.getSum(date) * rate
                          / (date - Date(date.getYear() - 1, 1, 1));    //年息
        if (interest != 0)
            record(date, interest, "Interest");
        acc.reset(date, getBalance());
    }
}


//CreditAccount类方法实现
//构造函数
CreditAccount::CreditAccount(const Date& date, const string& id, double credit, double rate, double fee)
    :Account(date, id), credit(credit), rate(rate), fee(fee), acc(date, 0){ }
//存入方法重写
void CreditAccount::deposit(const Date& date, double amount, const string& desc){
    record(date, amount, desc);
    acc.change(date, getDebt());
}
//取出方法重写
void CreditAccount::withdraw(const Date& date, double amount, const string& desc){
    if (amount-getBalance() > credit)
        error("not enough credit");      //信用额度不足
    else {
        record(date, -amount, desc);
        acc.change(date, getDebt());
    }
}
//计息方法重写(每月1日调用)
void CreditAccount::settle(const Date& date){
    double interest = acc.getSum(date) * rate;  //利息
    if (interest != 0)
        record(date, interest, "Interest");
    if (date.getMonth() == 1)
        record(date, -fee, "Annual fee");
    acc.reset(date, getDebt());
}
//显示账户信息方法重写
void CreditAccount::show(ostream &out) const {
    Account::show(out);
    out << "\tAvailable credit: " << getAvailableCredit();
}
