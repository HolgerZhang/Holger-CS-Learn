//������е�ˮ�ɻ���
#include<iostream>
#include<cmath>
using namespace std;

//function declare
bool isNarcissistic(int num);

int main() {
	for (int i = 100; i < 1000; ++i) {
		if (isNarcissistic(i)) {
			cout << i << ' ';
		}
	}
	cout << endl;
	return 0;
}

//function define
/*===============================
�����������ж�һ���������Ƿ���ˮ�ɻ���
����˵����
	int num:���жϵ�������
����ֵ˵����
	true-��ˮ�ɻ�����false-����ˮ�ɻ���
===============================*/
bool isNarcissistic(int num) {
	if (num >= 1000 || num < 100) {
		return false;
	}
	int sum = 0;
	sum += (int)pow(num / 100, 3);
	sum += (int)pow(num % 100 / 10, 3);
	sum += (int)pow(num % 10, 3);
	return (sum == num);
}
