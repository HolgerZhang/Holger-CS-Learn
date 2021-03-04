//角谷猜想
#include<iostream>
using namespace std;

int main()
{
	int num = 0, cnt = 0;
	cout << "请输入一个正整数：";
	cin >> num;
	while (num != 1) {
		cnt++;
		int last = num;
		switch (num % 2) {
		case 0:	//偶数
			num /= 2;
			cout << last << "/2=" << num << endl;
			break;
		case 1:	//奇数
			num = 3 * last + 1;
			cout << "3*" << last << "+1=" << num << endl;
			break;
		}
	}
	cout << "共运算了" << cnt << "步" << endl;
	return 0;
}