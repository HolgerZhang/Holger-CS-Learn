//函数默认值参数，指针的sizeof
#include <cstdlib>
#include <iostream>
using namespace std;

void delay(int x = 1000)
{
	for (int i = 0; i < x; i++) {
		for (int i = 0; i < x; i++);
	}
	
}

int main()
{
//	for (int i = 0; i < 1000; i++) {
//		cout << '\r' << rand() % 9000 + 1000;
//		delay(1000);
//	}
	int num = 0;
	char ch = 'a';
	cout << sizeof(num) << endl;
	cout << sizeof(ch) << endl;
	int* p1;
	char* p2;
	cout << sizeof(p1) << endl;
	cout << sizeof(p2) << endl;

	return 0;
}