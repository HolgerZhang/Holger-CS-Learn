/**
 * @file    E02.cpp
 * @create  2020/05/04
 * @encoding UTF-8
 * @author  Holger
 * @description
 * 实验六 运算符重载、静态成员
 * E03.	现需要处理银行活期存款业务，设账户类为，CAount，请根据如下需求实现该类，并在 main函数中测试。
 *      - 每个账户需要有一个浮点型的成员m_Money用于存储账上余额；
 *      - 每个账户需要描述存款的日期；
 *      - 银行的年利息采用浮点型静态数据成员m_InterestRate描述，从而避免为每个账户存储利息；
 *      - 为年利息成员提供静态成员SetInterestRate进行设置；
 *      - 为年利息成员提供静态成员GetInterestRate进行获取
 *      - 提供存款成员函数SaveMoney；
 *      - 提供取款成员函数LendMoney；
 *      - 提供计算利息函数CalcInterest；
 *      - 提供结算利息函数SaveInterest，该函数将计算出的利息结算到本金中。
 *      为简化计算，请考虑以下定义或限制：
 *          (1). 本题目不考虑闰年，每个月都认为30天，一年认为360天。
 *          (2). 存款仅考虑发生一次！
 *          (3). 取款允许发生多次，但取款是否允许需要考虑“本金是否足够”的条件
 */

#include <iostream>
#include <iomanip>

using namespace std;

// 表示日期
struct Date {
    int year;   // 年
    int month;  // 月
    int day;    // 日
    // 计算距离另一日期有多少天
    int distance(const Date &other) const {
        return ((other.year - this->year) * 360 + (other.month - this->month) * 30 + (other.day - this->day) + 1);
    }
};

// 账户类
class CAount {
private:
    double m_Money;    // 余额
    Date m_date;       // 存款日期
    static double m_InterestRate;   // 年利率
    double CalcInterest(int year, int month, int day, double money) const;    // 计算利息函数

public:
    // 设置银行年利息
    static void SetInterestRate(double interestRate) {
        CAount::m_InterestRate = interestRate;
    }

    // 获取银行年利息
    static double GetInterestRate() {
        return CAount::m_InterestRate;
    }

    // 存款成员函数
    void SaveMoney(int year, int month, int day, double money);
    // 取款成员函数
    double LendMoney(int year, int month, int day, double money);
    // 结算利息函数，将计算出的利息结算到本金中
    void SaveInterest(int year, int month, int day);
    // 输出账户信息
    friend ostream &operator<<(ostream &out, const CAount &temp);
};

// 类外初始化
double CAount::m_InterestRate = 0;   // 年利率

// 存款成员函数
void CAount::SaveMoney(int year, int month, int day, double money) {
    m_date = Date{year, month, day};
    m_Money = money;
}

// 取款成员函数
double CAount::LendMoney(int year, int month, int day, double money) {
    if (money > m_Money) {
        cout << "Insufficient principal!" << endl;
        return 0.0;
    }
    m_Money -= money;
    return (money + CalcInterest(year, month, day, money));
}

// 计算利息函数
double CAount::CalcInterest(int year, int month, int day, double money) const {
    return (money * m_InterestRate * m_date.distance({year, month, day}) / 360.0);
}

// 结算利息函数，将计算出的利息结算到本金中
void CAount::SaveInterest(int year, int month, int day) {
    m_Money += CalcInterest(year, month, day, m_Money);
    m_date = Date{year, month, day};
}

// 输出日期
ostream &operator<<(ostream &out, const Date &temp) {
    out << setiosflags(ios::right) << setfill('0');
    out << setw(4) << temp.year << "-" << setw(2) << temp.month << "-" << setw(2) << temp.day;
    out << resetiosflags(ios::right) << setfill(' ');
    return out;
}

// 输出账户信息
ostream &operator<<(ostream &out, const CAount &temp) {
    out << "[ACCOUNT] Balance: $" << setiosflags(ios::fixed | ios::left) << setprecision(2) << temp.m_Money;
    out << resetiosflags(ios::fixed | ios::left) << "\tDate of deposit: " << temp.m_date;
    return out;
}

// 主函数
int main() {
    // 设置年利率为3.6%
    CAount::SetInterestRate(0.036);
    cout << "Annual interest rate: " << CAount::GetInterestRate() << endl;

    CAount myAccount;
    double money;
    // 于 2014-1-1 到银行存了 100000 元
    cout << "2014-1-1\tDeposit $100000.00" << endl;
    myAccount.SaveMoney(2014, 1, 1, 100000);
    cout << "My Account: " << myAccount << endl;
    // 2014-3-10 银行“结算利息”一次
    cout << "2014-3-10\tSettlement interest" << endl;
    myAccount.SaveInterest(2014, 3, 10);
    cout << "My Account: " << myAccount << endl;
    // 2014-3-30 取款 200000
    cout << "2014-3-30\tTry to Withdraw $200000.00" << endl;
    money = myAccount.LendMoney(2014, 3, 30, 200000);
    cout << "Withdraw $" << setiosflags(ios::fixed | ios::left) << setprecision(2) << money
         << resetiosflags(ios::fixed | ios::left) << endl;
    cout << "My Account: " << myAccount << endl;
    // 2014-4-4 取款 50000
    cout << "2014-4-4\tTry to Withdraw $50000.00" << endl;
    money = myAccount.LendMoney(2014, 4, 4, 50000);
    cout << "Withdraw $" << setiosflags(ios::fixed | ios::left) << setprecision(2) << money
         << resetiosflags(ios::fixed | ios::left) << endl;
    cout << "My Account: " << myAccount << endl;

    return 0;
}
