//值传递与数组作为函数参数
#include<iostream>
using namespace std;

//值传递：单向传递
void exchange(int num1, int num2);
//数组作为函数参数（数组名即地址，按地址传递）：双向传递
void change(int nums[], int size);

int main() {
	/*
	int m = 3, n = 5;
	cout << m << ' ' << n << endl;
	exchange(m, n);
	cout << m << ' ' << n << endl;
	*/

	int arr1[5] = { 0 };
	change(arr1, 5);
	for (int i = 0; i <= 4; i++) {
		cout << arr1[i] << ' ';
	}
	cout << endl;
	return 0;
}

void change(int nums[], int size) {
	for (int i = 0; i < size; i++) {
		nums[i] = i;
	}
}

void exchange(int num1, int num2) {
	int temp = num1;
	num1 = num2;
	num2 = temp;
	cout << num1 << " " << num2 << endl;
}
