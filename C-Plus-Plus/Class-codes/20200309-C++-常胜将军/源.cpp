//常胜将军
#include<iostream>
using namespace std;

int main()
{
	int coins = 21;
	do {
		int PersonGet, ComputerGet;
		while (1) {
			cout << "现在有" << coins << "枚硬币。";
			cout << "请输入你要取的硬币的数量（1-4枚）：";
			cin >> PersonGet;
			if (PersonGet >= 1 && PersonGet <= 4 && PersonGet <= coins)
				break;
			cout << "你取走的数量是不合法的，请重新输入。" << endl;
		}
		ComputerGet = 5 - PersonGet;
		coins -= ComputerGet+ PersonGet;
		cout << "电脑取走了" << ComputerGet << "枚硬币。" << endl;
	} while (coins != 1);
	cout << "你输了！你只能取走这一枚硬币。" << endl;
	return 0;
}