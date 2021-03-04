//二维指针：指向指针的指针
#include<iostream>
using namespace std;

int main02()
{
	char* months[12] = {		//指针数组，12个字符数组不必连续，但多了指针数组的空间
		"January", "February", "March",     "April",   "May",      "June",
		"July",    "August",   "September", "October", "November", "December"
	};
	int num;
	cout << "请输入一个数字："; cin >> num;
	if (num >= 1 && num <= 12) {
		cout << months[num - 1] << endl;
	}
	else {
		cout << "输入错误" << endl;
	}
	return 0;
}


int main01()
{
	char months[12][16] = {	//是连续的，内存浪费：12*16
		"January", "February", "March",     "April",   "May",      "June",
		"July",    "August",   "September", "October", "November", "December"
	};
	int num;
	cout << "请输入一个数字："; cin >> num;
	if (num >= 1 && num <= 12) {
		cout << months[num - 1] << endl;
	}
	else {
		cout << "输入错误" << endl;
	}
	return 0;
}