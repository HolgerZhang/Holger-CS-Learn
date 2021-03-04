//输出所有的水仙花数
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
本函数用于判断一个正整数是否是水仙花数
参数说明：
	int num:待判断的正整数
返回值说明：
	true-是水仙花数；false-不是水仙花数
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
