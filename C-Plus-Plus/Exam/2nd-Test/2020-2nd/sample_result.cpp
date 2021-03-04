#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;


// deposit类声明
class deposit {
private:
    string name; // 账户名称
    double balance, loan, charge; // 账户存款余额, 账户贷款余额, 每次还贷金额
public:
    // 构造函数，name默认值为“NoName”，其余参数默认值为0.0
    deposit(const string& name = "NoName", double balance = 0.0, double loan = 0.0, double charge = 0.0)
        : name(name), balance(balance), loan(loan), charge(charge) { }

    // 设置账户名称
    void setName(const string& name);

    // 执行还贷操作
    bool pay();

    // 将当前对象的每次还贷金额charge增加100
    deposit operator++(int);

    // 显示一个对象的信息
    friend ostream& operator<<(ostream& out, const deposit& self);

};


// 全局函数声明

int inputData(const string& filePath, vector<deposit>& accounts); // 读取文件函数
void incData(vector<deposit>& accounts); // 所有账户的还贷金额增加100
int decData(vector<deposit>& accounts); // 所有账户执行一次还贷操作，返回无法完成还贷的账户数
void outPut(const vector<deposit>& accounts); // 用于把向量中的数据显示输出


// 主函数入口
int main() {
    vector<deposit> v_acc;
    string path = "d:\\account.txt";
    inputData(path, v_acc);
    outPut(v_acc);
    cout << "-------------------------------" << endl;
    incData(v_acc);
    outPut(v_acc);
    cout << "-------------------------------" << endl;
    cout << "can not pay = " << decData(v_acc) << endl;
    outPut(v_acc);
    return 0;
}


// 类成员函数实现

// 设置账户名称
void deposit::setName(const string& name) {
    this->name = name;
}

// 执行还贷操作
bool deposit::pay() {
    // 余额balance不大于还贷金额charge，则不还贷，原名称后面加“(*)”
    if (!(balance > charge)) {
        name += "(*)";
        return false;
    }
    // 还贷
    // 如果loan大于charge，则还贷金额为charge，否则还贷金额为loan
    double this_charge = (loan > charge) ? charge : loan;
    balance -= this_charge;
    loan -= this_charge;
    return true;
}

// 将当前对象的每次还贷金额charge增加100
deposit deposit::operator++(int) {
    deposit backup(*this); // 后置++返回一个备份
    charge += 100;
    return backup;
}

// 显示一个对象的信息

ostream& operator<<(ostream& out, const deposit& self) {
    // name占10列并左对齐，balance、loan、charge各占15列并精确到小数点后2位
    out << setiosflags(ios::left);
    out << setw(10) << self.name;
    out << setiosflags(ios::right | ios::fixed) << setprecision(2);
    out << setw(15) << self.balance;
    out << setw(15) << self.loan;
    out << setw(15) << self.charge;
    out << resetiosflags(ios::left | ios::right | ios::fixed);
    return out;
}


// 全局函数实现

// 读取文件函数，结果存放在向量accounts中
int inputData(const string& filePath, vector<deposit>& accounts) {
    ifstream inFile(filePath); // 打开文件
    // 检测文件是否打开成功
    if (!inFile.is_open()) {
        return -1;
    }

    while (!inFile.eof()) {
        // 读取数据
        string line; // 文件中的一行
        string name; // 账户名称
        double balance, loan, charge; // 账户存款余额, 账户贷款余额, 每次还贷金额
        getline(inFile, line);
        if (line.empty()) { // 防止读入空行
            continue;
        }
        istringstream is(line);
        is >> name >> balance >> loan >> charge;
        // 存入数据
        accounts.push_back(deposit(name, balance, loan, charge));
    }

    inFile.close(); // 关闭文件
    return 0;
}

// 所有账户的还贷金额增加100
void incData(vector<deposit>& accounts) {
    for (deposit& account : accounts) {
        account++;
    }
}

// 所有账户执行一次还贷操作，返回无法完成还贷的账户数
int decData(vector<deposit>& accounts) {
    int number = 0;
    for (deposit& account : accounts) {
        if (!account.pay()) { // 无法完成还贷，统计数+1
            number++;
        }
    }
    return number;
}

// 用于把向量中的数据显示输出
void outPut(const vector<deposit>& accounts){
    for (const deposit& account : accounts) {
        cout << account << endl;
    }
}
