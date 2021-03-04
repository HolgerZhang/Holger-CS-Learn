#include <iostream>
using namespace std;
class Grandam {
public:
    virtual void introduce_self()  // 定义虚函数introduce_self()
    {
        cout << "I am grandam." << endl;
    }
};
class Mother :public Grandam {
public:
    void introduce_self()     // 重新定义虚函数introduce_self()
    {
        cout << "I am mother." << endl;
    }
};
class Daughter :public Mother {
public:
    void introduce_self()     // 重新定义虚函数introduce_self()
    {
        cout << "I am daughter." << endl;
    }
};
void main()
{
    Grandam* ptr;
    Grandam g;
    Mother m;
    Daughter d;
    ptr = &g;
    ptr->introduce_self();//调用基类Grandam的introduce_self()
    ptr = &m;
    ptr->introduce_self();// 调用派生类Mother的introduce_self()
    ptr = &d;
    ptr->introduce_self();    //调用派生类
                                              //  Daughter的introduce_self()
}
