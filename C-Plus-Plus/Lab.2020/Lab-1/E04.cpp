/**
 * @file    E04.cpp
 * @create  2020/03/03
 * @encoding GBK
 * @author  Holger
 * @description
 *  һֻ����ڿ��ˣ�Ҫ��20��ˮ���ܽ�ʣ�������ֻ��һ����h���ף�����뾶Ϊr���׵�СԲͰ(h��r��������)��
 *  �ʴ�������Ҫ�ȶ���Ͱˮ�Ż��ʡ���ע��СԲͰ����h�͵���뾶r���û����룬��λĬ�������ס���
 */
#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.14159;	//Բ����

int main()
{
	int h, r;
	//����СԲͰ����h�͵���뾶r
	cout << "СԲͰ����h=";	cin >> h;
	cout << "����뾶r=";		cin >> r;
	//����Ͱ�������
	int num = ceil(20000 / (PI * h * r * r));
	cout << "��������Ҫ��" << num << "Ͱˮ�Ż���" << endl;
	return 0;
}