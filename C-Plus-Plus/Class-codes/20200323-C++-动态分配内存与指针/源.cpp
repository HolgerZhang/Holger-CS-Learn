//��̬�����ڴ���ָ��
#include<iostream>
using namespace std;

int main()
{
	int count;
	cin >> count;
	int* p = new int[count];		//��̬�����ڴ棬p���ײ�Ҫ�޸�
	delete p;		//new�����ڴ��һ��Ҫdelete�������˳�ʱҲ����գ�
	//�����������ʱ�䳤�󣬳������bug
	return 0;
}