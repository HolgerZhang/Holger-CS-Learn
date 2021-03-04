//account.h
#ifndef __ACCOUNT_H
#define __ACCOUNT_H

#include "date.h"
#include "accumlator.h"
#include <map>
#include <string>
#include <istream>
#include <stdexcept>
using namespace std;

class Account;      //前引声明


class AccountRecord {           //账目记录类
private:
    Date date;                  //日期
    const Account* account;     //账户指针
    double amount;              //金额
    double balance;             //余额
    string desc;                //信息
public:
    //构造函数
    AccountRecord(const Date& date, const Account* account,
                  double amount, double balance, const string& desc);
    void show() const ;         //输出当前记录
};


class AccountException : public runtime_error{  //账户错误信息类
private:
    const Account* account;     //记录出错账户信息
public:
    //构造函数
    AccountException(const Account* account, const string &msg)
            :runtime_error(msg), account(account){ }
    //获取账户信息接口
    const Account* getAccount() const { return account; }
};


//定义记录信息用的multimap类型RecordMap
typedef multimap<Date, AccountRecord> RecordMap;

class Account {                 //账户基类
private:
    string id;                  //账号数据
    double balance;             //余额数据
    static double total;        //所有账户的总金额-静态数据
    static RecordMap recordMap; //账目记录-静态数据
protected:
    //构造函数, 供派生类调用, id为账户
    Account(const Date& date, const string& id);
    //记账方法
    void record(const Date& date, double amount, const string& desc);
    //抛出错误信息的方法
    void error(const string& msg) const throw(AccountException);
public:
    //私有数据的公有接口
    const string& getId() const { return id; }
    double getBalance() const { return balance; }
    static double getTotal() { return total;}
    //显示账户信息方法, 虚函数
    virtual void show(ostream &out) const;
    //存入方法, 纯虚函数
    virtual void deposit(const Date& date, double amount, const string& desc) = 0;
    //取出方法, 纯虚函数
    virtual void withdraw(const Date& date, double amount, const string& desc) = 0;
    //计息方法, 纯虚函数 (每月1日调用)
    virtual void settle(const Date& date) = 0;
    //查询指定日期内的账目记录
    static void query(const Date& begin, const Date& end) throw(runtime_error);
};

//Account类及其子类用于输出账户信息的全局函数
inline ostream &operator<<(ostream &out, const Account &account);


class SavingsAccount : public Account  {        //储蓄账户类
private:
    Accumlator acc;                             //计算利息累加器
    double rate;                                //存款年利率数据
public:
    SavingsAccount(const Date& date, const string& id, double rate);    //构造函数
    double getRate() const { return rate; }     //私有数据rate的公有接口
    //存入方法重写
    void deposit(const Date& date, double amount, const string& desc) override;
    //取出方法重写
    void withdraw(const Date& date, double amount, const string& desc) override;
    //计息方法重写(每年1月1日调用)
    void settle(const Date& date) override;
};


class CreditAccount : public Account {          //信用卡账户类
private:
    Accumlator acc;             //计算利息累加器
    double credit;              //信用额度
    double rate;                //欠款日利率数据
    double fee;                 //年费
    //获得欠款额
    double getDebt() const {
        double balance = getBalance();
        return (balance<0 ? balance : 0);
    }
public:
    //构造函数
    CreditAccount(const Date& date, const string& id, double credit, double rate, double fee);
    //私有数据的公有接口
    double getCredit() const { return credit; }
    double getRate() const { return rate; }
    double getFee() const { return fee; }
    //获取可用信用额度
    double getAvailableCredit() const {
        if (getBalance() < 0)
            return credit+getBalance();
        else
            return credit;
    }
    //存入方法重写
    void deposit(const Date& date, double amount, const string& desc) override;
    //取出方法重写
    void withdraw(const Date& date, double amount, const string& desc) override;
    //计息方法重写(每月1日调用)
    void settle(const Date& date) override;
    //显示账户信息方法重写
    void show(ostream &out) const override ;
};


#endif //__ACCOUNT_H
