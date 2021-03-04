//2020-3-21 10:49:29
//指针与数组
#include<iostream>
//#include<cstring>
using namespace std;

#define SIZE 10
int myStrlen(char buff[]);

int main()
{
	int array1[SIZE];
	//常规初始化
	for (int i = 0; i < SIZE; i++) {
		array1[i] = i;
	}
	for (int i = 0; i < SIZE; i++) {
		cout << i[array1] << '\t';	//这样也是可以的 相当于i+array1
	}
	cout << endl;
	
	//使用指针
	int* p;
	//cout << *p;	指针不知道指向哪里，不要去它的内容
	p = array1;	//数组名即首元素地址
	
	//如果一个指针指向了数组的首地址，该指针就可以当数组名用
	for (int i = 0; i < SIZE; i++) {
		cout << p[i] << '\t';	//指针名当数组名用
	}
	cout << endl;

	//指针+-常量=指针；指针-指针=距离
	//版本1
	for (int i = 0; i < SIZE; i++) {
		*(p+i) = i;
	}
	for (int i = 0; i < SIZE; i++) {
		cout << *(p + i) << '\t';
	}
	cout << endl;
	//版本2
	for (int i = 0; i < SIZE; i++) {
		*p = i;
		p++;
	}
	p = array1;	//指针回到首地址，防止指针越界
	for (int i = 0; i < SIZE; i++) {
		cout << *p << '\t';
		p++;
	}
	cout << endl;

	//char buff1[128] = "hello";
	//strcpy(buff1, buff1 + 1); 删掉buff1的第一个字符

	return 0;
}

//用指针计算字符串长度
int myStrlen(char buff[])
{
	char* p = buff;
	while (*p) p++;
	return p - buff;
}
