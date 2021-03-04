//猜数字
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

int main()
{
	//产生随机数
	srand((unsigned)time(NULL));
	int num = rand() % 50 + 50;
	int guess, count = 0;
	//cout << num << endl;
	do {
		cout << "猜一个1到10000的数字：";
		cin >> guess;
		count++;
		if (guess > num) {
			cout << "您猜的数字偏大，再试一次吧！" << endl;
		}
		else if (guess < num) {
			cout << "您猜的数字偏小，再试一次吧！" << endl;
		}
	}while (guess != num);
	cout << "您猜对了！正确的数字是" << num << "，您一共猜了" << count << "次。" << endl;
	return 0;
}