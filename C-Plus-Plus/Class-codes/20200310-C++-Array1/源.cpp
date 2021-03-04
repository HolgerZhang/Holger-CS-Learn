#include<iostream>
using namespace std;

int main() {
	int array1[10] = { 0 };
	for (int i = 0; i <= 30000; i++) {
		cout << array1[i] << '\t';
	}
	return 0;
}