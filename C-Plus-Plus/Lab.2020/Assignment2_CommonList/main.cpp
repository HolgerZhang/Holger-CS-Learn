/**
 * @file    LinkedList.h
 * @create  2020/05/29
 * @encoding UTF-8
 * @author  Holger
 * @details 自己测试两个类的代码
 */

#include "LinkedList.h"

using namespace std;

class CData : public CNode {
    int num;

public:
    CData(int num = 0) : num(num) {}

    int getNum() const { return num; }

    void setNum(int num) { this->num = num; }

    ~CData() override = default;

    std::string toString() const override {
        ostringstream out;
        out << num;
        return out.str();
    }

    bool operator<(const CNode &other) const override {
        const CData &data = (CData &) other;
        return num < data.num;
    }

    bool operator>(const CNode &other) const override {
        const CData &data = (CData &) other;
        return num > data.num;
    }


    bool operator==(const CNode &other) const override {
        const CData &data = (CData &) other;
        return num == data.num;
    }

};

ostream &operator<<(ostream &out, const CData &data) {
    out << data.toString();
    return out;
}


int main() {
    CLinkedList list;
    cout << list << endl;

    // 疑问：如何将动态构造对象封装到CLinkedList类中（无法做到的原因：在CLinkedList类中不知道要new的对象所属的派生类）
    // 这样一来难以进行复制构造（目前还没想出解决办法）
    // 同时也没能实现一些预先设计好的CLinkedList类的方法（具体在头文件中说明）

    list.push_back(new CData(3));
    list.push_back(new CData(4));
    list.push_back(new CData(5));
    cout << list << endl;

    cout << list.length() << ',' << *(CData *) list.front() << ',' << *(CData *) list.back() << endl;
    auto find_it1 = list.find(CData(4));
    if (find_it1 != CLinkedList::None) {
        cout << "got 4" << endl;
    }
    auto find_it2 = list.find(CData(100));
    if (find_it2 != CLinkedList::None) {
        cout << "got 100" << endl;
    }

    // 这里强制类型转换才能调到派生类的属性和方法（有点不方便使用者）

    for (int i = 0; i < list.length(); i++) {
        ((CData &) list[i]).setNum(10 + i);
        // 只能用引用，否则报错：不存在适当转换
    }

    for (int i = 0; i < list.length(); i++) {
        cout << (CData &) list[i] << endl;
    }

    // list[3];

    list.push_front(new CData(-5));
    list.push_front(new CData(-3));

    cout << list << endl;

    list.insert(1, new CData(0));
    cout << list << endl;

    list.sort(true);
    cout << list << endl;

    list.pop(3);
    cout << list << endl;
    list.pop_back();
    cout << list << endl;
    list.pop_front();
    cout << list << endl;

    list.clear();
    cout << list << endl;

    list.push_back(new CData(100));
    list.sort();
    cout << list << endl;
    cout << *(CData *) list.front() << endl;
    cout << *(CData *) list.back() << endl;

    return 0;
}