//36块砖头36人搬, 男人：4块, 女人：2块, 小孩：2人搬1块
#include<iostream>
using namespace std;

int main()
{
	int male, female, child;
	for (male = 0; male <= 9; male++) {
		for (female = 0; female <= 18; female++) {
			child = 36 - male - female;
			if (4 * male + 2 * female + child*0.5 ==36) {
				cout << male << "男人，" << female << "女人，" << child << "小孩。" << endl;
			}
		}
	}
	return 0;
}