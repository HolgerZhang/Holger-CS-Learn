/**
 * @file    3.cpp
 * @create  2020/03/18
 * @encoding GBK
 * @author  Holger
 * @description
 * ʵ���� ����
 *  ���һ������Calc��
 *  ����ԭ��Ҫ��	void Calc(int Num1, int Num2, int &GCD, int &LCM);
 *  �������ܣ�
 *          - ��������������Ϊ������
 *          - ��������Լ������С������������Ҫ��Calc������ʹ�������������
 *          - �����ں���������ʹ�����á�
 *  main�������ܣ�	���Ժ������ܡ�
 */
#include <iostream>

using namespace std;

void Calc(int Num1, int Num2, int &GCD, int &LCM);

int main() {
    int num1, num2;
    cout << "�����������������ÿո�ֿ���";
    cin >> num1 >> num2;
    int GCD = 0, LCM = 0;        //���Լ������С������
    Calc(num1, num2, GCD, LCM);    //���
    cout << "���Լ����" << GCD << endl;
    cout << "��С��������" << LCM << endl;
    return 0;
}

/*=================================
�����������������Լ������С������
����˵����
	Num1��Num2:��������
	GCD:������Լ���Ľ��
	LCM:�����С�������Ľ��
����ֵ˵����
	��ʵ�ʷ���ֵ�������GCD��LCM����
=================================*/
void Calc(int Num1, int Num2, int &GCD, int &LCM) {
    if (Num1 == 0 && Num2 == 0) {
        //������Ϊ0ʱ��������0����ֹ�������
        GCD = 0;
        LCM = 0;
        return;
    }
    int product = Num1 * Num2;    //�����˻�
    //շת����������Լ����ֱ��Num2Ϊ0Ϊֹ��Num1Ϊ���Լ��
    int temp;
    while (Num2) {
        temp = Num2;
        Num2 = Num1 % Num2;
        Num1 = temp;
    }
    GCD = Num1;
    //��С������=�����˻��������Լ��
    LCM = product / GCD;
}
