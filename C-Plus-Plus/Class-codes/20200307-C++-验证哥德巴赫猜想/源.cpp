//验证哥德巴赫猜想
#include<iostream>
#include<cmath>
using namespace std;

bool isPrime(int num)
{
	if (num <= 1) {
		return false;
	}
	int cnt = 2;
	int qnum = int(sqrt(num)) + 1;	//空间换时间
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
	cout << "请输入一个大于2的偶数：";
	cin >> num;
	if (num <= 2 || num % 2 != 0) {
		cout << "输入有误" << endl;
		return 0;
	}
	for (int cnt = 2; cnt < num/2; cnt++) {
		if (!isPrime(cnt)) {
			continue;
		}
		if (isPrime(num - cnt)) {
			cout << num << "可以分解为" << cnt << "和" << num - cnt << endl;
			break;
		}
	}
	return 0;
}
