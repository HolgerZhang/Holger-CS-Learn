//输出所有的勾股数
#include<iostream>
#include<cmath>
using namespace std;

int main()
{
	int num1, num2, num3;
	for (num1 = 1; num1 <= 100; num1++) {
		for (num2 = num1 + 1; num2 <= 100; num2++) {
			num3 = sqrt(num1 * num1 + num2 * num2);
			if (num1 * num1 + num2 * num2 == num3 * num3) {
				cout << num1 << ' ' << num2 << ' ' << num3 << endl;
			}
		}
	}
	return 0;
}