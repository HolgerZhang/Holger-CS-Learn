#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include "date.h"
#include "account.h"
#include <vector>

struct deleter{     //释放new的内存空间, 可()调用
    template <class T>
    void operator()(T*p){ delete p; }
};


class Controller {              //运行控制类
private:
    Date date;                  //当前日期
    vector<Account*> accounts;  //账户列表
    bool end;                   //用户是否输入了命令
public:
    Controller(const Date &date):date(date), end(false) { } //构造函数
    ~Controller();              //析构函数
    //私有数据的公有接口
    const Date &getDate() const { return date; }
    bool isEnd() const { return end; }
    //执行一条命令, 并判段状态是否改变了状态(是否需要保存命令)
    //para2 bool 表示是否为运行状态(接受用户输入命令状态), 用于区分#的作用
    bool run(const string &cmdLine, bool runtime=true);
    //显示帮助信息
    void help() const ;
};


#endif //__CONTROLLER_H
