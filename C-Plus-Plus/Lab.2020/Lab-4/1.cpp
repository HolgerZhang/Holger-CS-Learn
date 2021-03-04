/**
 * @file    1.cpp
 * @create  2020/03/18
 * @encoding GBK
 * @author  Holger
 * @description
 * ʵ���� ����
 *  ��д����IsPrime��
 *  ����ԭ��Ҫ��	int IsPrime(int Num);
 *  �������ܣ�		�ж�һ�������Ƿ���������
 *  main�������ܣ�	��1000���ڵ�����������ÿ��8���������Ļ�ϡ�
 */
#include <iostream>
#include <cmath>

using namespace std;

int IsPrime(int Num);

int main() {
    int i, cnt;    //i��2ȡ��1000��cntͳ������ĸ���
    for (i = 2, cnt = 0; i <= 1000; i++) {
        if (IsPrime(i)) {
            cout << i << '\t';
            cnt++;
            if (cnt % 8 == 0) {    //ÿ��8��
                cout << endl;
            }
        }
    }
    return 0;
}

/*==========================
�ж�һ�������Ƿ�������
����˵����
	Num:���жϵ�����
����ֵ˵����
	0����Num����������
	1����Num������
==========================*/
int IsPrime(int Num) {
    if (Num <= 1) {
        return 0;
    }
    int End = int(sqrt(Num));    //ѭ���յ�����
    for (int i = 2; i <= End; i++) {
        if (Num % i == 0) {
            return 0;
        }
    }
    return 1;
}
