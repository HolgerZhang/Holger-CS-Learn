#include <iostream>
using namespace std;

class CGateCount {
public:
    // 带1个参数count的构造函数
    CGateCount(int count = 0): m_count(count) {
        m_gateNum = ++m_totalGate; // 本机编号等于闸机总数加1, 闸机总数加1
        m_totalCount += count; // 合计通过人数加count
    }

    // 拷贝构造函数
    CGateCount(const CGateCount&): m_count(0) {
        m_gateNum = ++m_totalGate; // 本机编号等于闸机总数加1, 闸机总数加1
    }

    // 析构函数
    ~CGateCount() {
        m_totalGate--;
    }

    // 设置当日人数上限
    static void set_maxCount(int count) {
        m_maxCount = count;
    }

    // 返回所有闸机通过人数
    static int get_totalCount() {
        return m_totalCount;
    }

    // 实现返回当前闸机通过人数
    int get_count() const {
        return m_count;
    }

    // 前自增运算符++，将当前闸机通过人数和所有闸机通过人数加1
    CGateCount& operator++() {
        if (m_totalCount >= m_maxCount) {
            return *this;
        }
        m_totalCount++;
        m_count++;
        return *this;
    }

    // 后自增运算符++
    CGateCount operator++(int) {
        CGateCount backup(*this);
        ++(*this);
        return backup;
    }

    // 流输出运算，显示一个闸机的通过信息
    friend ostream& operator<<(ostream& out, const CGateCount& self);

private:
    static int m_maxCount; // 当日人数上限
    static int m_totalGate; // 闸机总数
    static int m_totalCount; // 合计通过人数
    int m_gateNum; // 本闸机编号
    int m_count; // 本闸机通过人数
};

// 静态数据成员的初始化

int CGateCount::m_maxCount = 0;
int CGateCount::m_totalGate = 0;
int CGateCount::m_totalCount = 0;

// 流输出运算，显示一个闸机的通过信息
ostream& operator<<(ostream& out, const CGateCount& self) {
    out << "==========" << endl;
    out << "闸机编号：" << self.m_gateNum << endl;
    out << "通过人数：" << self.m_count << endl;
    out << "合计人数：" << self.m_totalCount << endl;
    out << "上限人数：" << self.m_maxCount << endl;
    out << "==========" << endl;
    return out;
}


void main() {
    CGateCount::set_maxCount(3000); //设置最大通过人数
    CGateCount gate1; //定义闸机对象
    gate1++;
    cout << gate1;
    CGateCount gate2(gate1); //定义闸机对象2
    (++gate2)++;
    cout << "gate2通过人数:" << gate2.get_count() << endl;
    cout << "合计通过人数:" << gate2.get_totalCount() << endl;

    CGateCount pGate3(2997);
    cout << "gate3通过人数:" << pGate3.get_count() << endl;
    cout << "合计通过人数:" << pGate3.get_totalCount() << endl;

    cout << ++gate2;
}
