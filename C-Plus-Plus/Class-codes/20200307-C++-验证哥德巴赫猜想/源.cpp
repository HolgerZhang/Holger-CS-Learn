//��֤��°ͺղ���
#include<iostream>
#include<cmath>
using namespace std;

bool isPrime(int num)
{
	if (num <= 1) {
		return false;
	}
	int cnt = 2;
	int qnum = int(sqrt(num)) + 1;	//�ռ任ʱ��
	while (cnt < qnum) {
		if (num % cnt == 0) {
			return false;
		}
		cnt++;
	}
	return true;
}

int main()
{
	int num;
	cout << "������һ������2��ż����";
	cin >> num;
	if (num <= 2 || num % 2 != 0) {
		cout << "��������" << endl;
		return 0;
	}
	for (int cnt = 2; cnt < num/2; cnt++) {
		if (!isPrime(cnt)) {
			continue;
		}
		if (isPrime(num - cnt)) {
			cout << num << "���Էֽ�Ϊ" << cnt << "��" << num - cnt << endl;
			break;
		}
	}
	return 0;
}
