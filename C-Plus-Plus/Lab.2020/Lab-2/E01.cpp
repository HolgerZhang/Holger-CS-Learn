/**
 * @file    E01.cpp
 * @create  2020/03/07
 * @encoding GBK
 * @author  Holger
 * @description ��д�����ӡ��ASCII���32��126��ASCII�ַ���ÿ�д�ӡ5������
 */
#include <iostream>

using namespace std;

int main() {
    char ch;    //�ַ�
    int i;        //�ۼƴ�ӡ���ַ���
    //��ӡ��ASCII���32��126��ASCII�ַ�
    for (ch = 32, i = 1; ch <= 126; ++ch, ++i) {
        cout << ch;
        if (i % 5 == 0)    //ÿ�д�ӡ5��
            cout << endl;
    }
    return 0;
}