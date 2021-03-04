#include <iostream>
using namespace std;
class Grandam {
public:
    virtual void introduce_self()  // �����麯��introduce_self()
    {
        cout << "I am grandam." << endl;
    }
};
class Mother :public Grandam {
public:
    void introduce_self()     // ���¶����麯��introduce_self()
    {
        cout << "I am mother." << endl;
    }
};
class Daughter :public Mother {
public:
    void introduce_self()     // ���¶����麯��introduce_self()
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
    ptr->introduce_self();//���û���Grandam��introduce_self()
    ptr = &m;
    ptr->introduce_self();// ����������Mother��introduce_self()
    ptr = &d;
    ptr->introduce_self();    //����������
                                              //  Daughter��introduce_self()
}
