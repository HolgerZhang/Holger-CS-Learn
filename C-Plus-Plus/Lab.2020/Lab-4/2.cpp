/**
 * @file    2.cpp
 * @create  2020/03/18
 * @encoding GBK
 * @author  Holger
 * @description
 * ʵ���� ����
 *  ��д����InverseBits��
 *  ����ԭ��Ҫ��	int InverseBits(int Num);
 *  �������ܣ�		��һ�������ĸ�λ���ֶԵ���
 *  main�������ܣ�	��д���Դ��룬��������������µ�������
 *  ʾ����			����123�����øú���֮�󣬵õ����Ϊ321
 */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int InverseBits(int Num);

int main() {
    int number;
    cout << "������һ��������";
    cin >> number;
    int newNumber = InverseBits(number);    //��λ���ֶԵ�������
    cout << "��λ���ֶԵ���Ϊ��" << newNumber << endl;
    return 0;
}

/*==========================
��һ�������ĸ�λ���ֶԵ�
����˵����
	Num:ԭ����
����ֵ˵����
	��λ���ֶԵ��������
==========================*/
int InverseBits(int Num) {
    bool flag = false;    //�������
    if (Num < 0) {
        flag = true;
        Num = -Num;        //ȡ����ֵ
    }
    vector<int> bits;    //Num�ӵ�λ����λ�ĸ�λ����
    do {
        bits.push_back(Num % 10);
    } while (Num /= 10);
    int result = 0;        //�Ե��������
    for (int i = 0; i < bits.size(); i++) {
        result += int(bits[i] * pow(10, bits.size() - 1 - i));
    }
    return (flag ? -result : result);
}
