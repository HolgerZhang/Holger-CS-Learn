//动态分配内存与指针
#include<iostream>
using namespace std;

int main()
{
	int count;
	cin >> count;
	int* p = new int[count];		//动态分配内存，p轻易不要修改
	delete p;		//new出来内存的一定要delete（程序退出时也会回收）
	//否则程序运行时间长后，程序会有bug
	return 0;
}