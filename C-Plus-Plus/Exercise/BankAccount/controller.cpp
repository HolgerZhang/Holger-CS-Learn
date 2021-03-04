#include "controller.h"
#include <sstream>
#include <algorithm>


//Controller类实现
//析构函数
Controller::~Controller() {
    for_each(accounts.begin(), accounts.end(), deleter());  //释放new的内存空间
    cout << "Program finished." << endl;
}

//执行一条命令, 并判段状态是否改变了状态(是否需要保存命令)
bool Controller::run(const string &cmdLine, bool runtime) {
    istringstream str(cmdLine);     //以命令创建字符串输入流
    char cmd;       //命令控制字符
    char type;      //账户类型
    int index, day; //账户编号, 下一个日期的day
    double amount, credit, rate, fee;   //账户数据信息
    string id, desc;//账户id, 操作信息
    Account *account;   //账户指针
    Date date1, date2;  //日期
    //读入一条命令并选择
    str >> cmd;
    switch (cmd) {
        case 'a':   //新建账户
            str >> type >> id;
            if (type == 's') {
                str >> rate;
                account = new SavingsAccount(date, id, rate);
            } else if (type == 'c'){
                str >> credit >> rate >> fee;
                account = new CreditAccount(date, id, credit, rate, fee);
            } else
                throw runtime_error("Invalid account type");
            accounts.push_back(account);
            return true;
        case 'd':   //存款
            str >> index >> amount;
            getline(str, desc);
            accounts[index]->deposit(date, amount, desc);
            return true;
        case 'w':   //取款
            str >> index >> amount;
            getline(str, desc);
            accounts[index]->withdraw(date, amount, desc);
            return true;
        case 'c':   //修改日期
            str >> day;
            if (day < date.getDay())
                throw runtime_error("You can't go to a previous day.");
            else if (day > date.getMaxDay())
                throw runtime_error("Invalid day.");
            else
                date = Date(date.getYear(), date.getMonth(), day);
            return true;
        case 'n':   //下一个月
            if (date.getMonth() == 12)
                date = Date(date.getYear() + 1, 1, 1);
            else
                date = Date(date.getYear(), date.getMonth() + 1, 1);
            for (auto & pAccount : accounts)
                pAccount->settle(date);
            return true;
        case 's':   //显示账户信息
            for (size_t i = 0; i < accounts.size(); ++i) {
                cout << '[' << i << "] ";
                accounts[i]->show(cout);
                cout << endl;
            }
            return false;
        case 'q':   //查询一段时间内的账目
            str >> date1 >> date2;
            Account::query(date1, date2);
            return false;
        case 'e':   //退出
            end = true;
            return false;
        case '#':   //注释(文件中以#开头的一行会视为注释), 仅在读取文件时有效
            getline(str, desc);
            if (!runtime)
                return false;
        default:    //不合法的命令
            throw runtime_error("Invalid command.");
    }
}

//显示帮助信息
void Controller::help() const {
    cout << "\nWelcome! Enter the command after \">>>\"." << endl;
    cout << "  =======================COMMAND=======================  " << endl;
    cout << "\tAdd account(a type id [credit] rate [fee])" << endl
         << "\t  TYPE:[s]SavingsAccount -> id rate" << endl
         << "\t       [c]CreditAccount  -> id credit rate fee" << endl
         << "\tDeposit    (d account amount desc)" << endl
         << "\tWithdraw   (w account amount desc)" << endl
         << "\tShow       (s)" << endl
         << "\tChange Day (c day)" << endl
         << "\tNext Month (n)" << endl
         << "\tQuery      (q yyyy-mm-dd yyyy-mm-dd)" << endl
         << "\tExit       (e)" << endl;
    cout << "  =====================================================  \n" << endl;
}
