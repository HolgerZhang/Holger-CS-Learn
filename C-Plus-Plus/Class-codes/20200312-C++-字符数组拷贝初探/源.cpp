//×Ö·ûÊý×é¿½±´³õÌ½
#include<iostream>
#include<cstring>
using namespace std;

int main()
{
	char buff1[10] = "hello";
	char buff2[10];
	int i = 0;
	while (buff2[i] = buff1[i++]);
	cout << buff2;
	return 0;
}