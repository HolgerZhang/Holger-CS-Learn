#include<iostream>
using namespace std;

void test() {
	static int num = 0;
	num++;
	cout << num << endl;
}


int main() {
	for (int i = 0; i <= 2; i++)
		test();
	return 0;
}