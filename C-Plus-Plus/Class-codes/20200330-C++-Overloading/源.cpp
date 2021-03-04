#include<iostream>
using namespace std;

template <typename T>
T myabs(T num) {
	return ((num > 0) ? num : -num);
}

int main()
{
	cout << myabs(-7.8) << endl;

	return 0;
}


/*
int myabs(int num)
{
	return ((num > 0) ? num : -num);
}
double myabs(double num)
{
	return ((num > 0) ? num : -num);
}
long myabs(long num)
{
	return ((num > 0) ? num : -num);
}
*/