#include<iostream>
using namespace std;

class B0 { //����B0����
public:
    void display() {
        //���г�Ա����
        cout << "B0::display()" << endl;
    }
};

class B1 : public B0 {
public:
    void display() { cout << "B1::display() " << endl; }
};

class D1 : public B1 {
public:
    void display() { cout << "D1::display() " << endl; }
};

void fun(B0* ptr) { // �ȶ�����ʵ�ֿ���չ�Ĺ���
    ptr->display(); //"����ָ��->��Ա��"
}

void main() //������
{
    B0 b0; //����B0�����
    B1 b1; //����B1�����
    D1 d1; //����D1�����
    B0* p; //����B0��ָ��
    p = &b0; //B0��ָ��ָ��B0�����
    fun(p);
    p = &b1; //B0��ָ��ָ��B1�����
    fun(p);
    p = &d1; //B0��ָ��ָ��D1�����
    fun(p);
}
