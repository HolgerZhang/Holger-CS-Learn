//��άָ�룺ָ��ָ���ָ��
#include<iostream>
using namespace std;

int main02()
{
	char* months[12] = {		//ָ�����飬12���ַ����鲻��������������ָ������Ŀռ�
		"January", "February", "March",     "April",   "May",      "June",
		"July",    "August",   "September", "October", "November", "December"
	};
	int num;
	cout << "������һ�����֣�"; cin >> num;
	if (num >= 1 && num <= 12) {
		cout << months[num - 1] << endl;
	}
	else {
		cout << "�������" << endl;
	}
	return 0;
}


int main01()
{
	char months[12][16] = {	//�������ģ��ڴ��˷ѣ�12*16
		"January", "February", "March",     "April",   "May",      "June",
		"July",    "August",   "September", "October", "November", "December"
	};
	int num;
	cout << "������һ�����֣�"; cin >> num;
	if (num >= 1 && num <= 12) {
		cout << months[num - 1] << endl;
	}
	else {
		cout << "�������" << endl;
	}
	return 0;
}