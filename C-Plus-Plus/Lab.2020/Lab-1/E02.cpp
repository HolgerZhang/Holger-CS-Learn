/**
 * @file    E02.cpp
 * @create  2020/03/03
 * @encoding GBK
 * @author  Holger
 * @description
 *  �Ӽ�������һ����ĸ������������Сд��ĸ���뽫��ת��Ϊ��д��ĸ�����
 *  ���������Ǵ�д��ĸ���뽫��ת��ΪСд��ĸ������������ԭ����������д����ʵ�֡�
 */
#include <iostream>

using namespace std;

int main() {
    char ch;
    //�Ӽ��̶�ȡһ���ַ�
    cout << "������һ���ַ���";
    cin >> ch;
    if (ch >= 'A' && ch <= 'Z')
        ch += 32;    //��д��ĸתСд��ĸ
    else if (ch >= 'a' && ch <= 'z')
        ch -= 32;    //Сд��ĸת��д��ĸ
    //���ת�������ĸ
    cout << "ת������ַ�Ϊ��" << ch << endl;
    return 0;
}