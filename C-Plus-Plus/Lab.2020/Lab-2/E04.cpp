/**
 * @file    E04.cpp
 * @create  2020/03/07
 * @encoding GBK
 * @author  Holger
 * @description
 *  ��Ԫǰ5���ͣ��ҹ���ѧ�������ڡ��㾭���������Ǯ�ټ����⣺
 *  ����һֵǮ�壬��ĸһֵǮ����������ֵǮһ����Ǯ��ټ����ʼ��̡�ĸ���������Σ�
 */
#include<iostream>
using namespace std;

/**�ټ���Ǯ���⣺
 * �蹫����xֻ��ĸ����yֻ����С����(100-x-y)ֻ
 * ����100Ǯ�����20ֻ������33ֻĸ��
 * 100Ǯ������ʽ��5x+3y+(100-x-y)/3=100
 * �����ã�7x+4y=100��*������ y=(100-7x)/4
 * ��x��0ȡ��20������y��ȡ����������㣨*��ʽ��Ϊ����
 */

int main()
{
	int cock, hen, chick;	//������ĸ����С��������
	//����100Ǯ�����20ֻ���������������0ȡ��20
	for (cock = 0; cock <= 20; ++cock) {
		hen = (100 - 7 * cock) / 4;		//����ĸ��
		if (7 * cock + 4 * hen == 100 && hen >= 0 && hen <=33) {
			//ĸ��ֻ����0��33ֻ��������㣨*��ʽ��Ϊ����
			chick = 100 - cock - hen;	//����С��
			cout << "����" << cock << "ֻ��"
				 << "ĸ��" << hen << "ֻ��"
				 << "С��" << chick << "ֻ��" << endl;
		}
	}
	return 0;
}