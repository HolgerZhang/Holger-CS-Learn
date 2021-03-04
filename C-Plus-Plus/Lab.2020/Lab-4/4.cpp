/**
 * @file    4.cpp
 * @create  2020/03/18
 * @encoding GBK
 * @author  Holger
 * @description
 * ʵ���� ����
 *  ��д�������غ���printOut�ֱ�ʵ�����������������������string�ַ���
 *  Ҫ�����£�
 *      - ��������ռ10�У��Ҷ���
 *      - �����ͣ���4λС��
 *      - �ַ�����ռ10�У��Ҷ���
 *  main��������д���Գ��򣬲��Գ����е����������������ַ������û�����
 */
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void printOut(int num);

void printOut(double num);

void printOut(const string &str);

int main() {
    //���Ը�����
    double numberDouble;
    cout << "������һ����������";
    cin >> numberDouble;
    printOut(numberDouble);
    cout << endl;

    //����������
    int numberInt;
    cout << "������һ����������";
    cin >> numberInt;
    printOut(numberInt);
    cout << endl;

    //�����ַ���
    string str;
    cout << "������һ���ַ�����";
    cin >> str;
    printOut(str);
    cout << endl;

    return 0;
}

/*=================================
�����������ռ10�У��Ҷ���
����˵����
	num:Ҫ�����������
����ֵ˵����
	�޷���ֵ
=================================*/
void printOut(int num) {
    cout << setw(10) << num;
}

/*=================================
�������������4λС��
����˵����
	num:Ҫ����ĸ�����
����ֵ˵����
	�޷���ֵ
=================================*/
void printOut(double num) {
    cout << setiosflags(ios_base::fixed);
    cout << setprecision(4) << num;
    cout << resetiosflags(ios_base::fixed);    //�ָ�cout״̬
}

/*=================================
����ַ�����ռ10�У��Ҷ���
����˵����
	str:Ҫ������ַ����ĳ�����
����ֵ˵����
	�޷���ֵ
=================================*/
void printOut(const string &str) {
    cout << setw(10) << str;
}
