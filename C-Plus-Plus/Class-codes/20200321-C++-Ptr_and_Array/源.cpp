//2020-3-21 10:49:29
//ָ��������
#include<iostream>
//#include<cstring>
using namespace std;

#define SIZE 10
int myStrlen(char buff[]);

int main()
{
	int array1[SIZE];
	//�����ʼ��
	for (int i = 0; i < SIZE; i++) {
		array1[i] = i;
	}
	for (int i = 0; i < SIZE; i++) {
		cout << i[array1] << '\t';	//����Ҳ�ǿ��Ե� �൱��i+array1
	}
	cout << endl;
	
	//ʹ��ָ��
	int* p;
	//cout << *p;	ָ�벻֪��ָ�������Ҫȥ��������
	p = array1;	//����������Ԫ�ص�ַ
	
	//���һ��ָ��ָ����������׵�ַ����ָ��Ϳ��Ե���������
	for (int i = 0; i < SIZE; i++) {
		cout << p[i] << '\t';	//ָ��������������
	}
	cout << endl;

	//ָ��+-����=ָ�룻ָ��-ָ��=����
	//�汾1
	for (int i = 0; i < SIZE; i++) {
		*(p+i) = i;
	}
	for (int i = 0; i < SIZE; i++) {
		cout << *(p + i) << '\t';
	}
	cout << endl;
	//�汾2
	for (int i = 0; i < SIZE; i++) {
		*p = i;
		p++;
	}
	p = array1;	//ָ��ص��׵�ַ����ָֹ��Խ��
	for (int i = 0; i < SIZE; i++) {
		cout << *p << '\t';
		p++;
	}
	cout << endl;

	//char buff1[128] = "hello";
	//strcpy(buff1, buff1 + 1); ɾ��buff1�ĵ�һ���ַ�

	return 0;
}

//��ָ������ַ�������
int myStrlen(char buff[])
{
	char* p = buff;
	while (*p) p++;
	return p - buff;
}
