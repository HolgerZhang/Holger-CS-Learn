//������
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

int main()
{
	//���������
	srand((unsigned)time(NULL));
	int num = rand() % 50 + 50;
	int guess, count = 0;
	//cout << num << endl;
	do {
		cout << "��һ��1��10000�����֣�";
		cin >> guess;
		count++;
		if (guess > num) {
			cout << "���µ�����ƫ������һ�ΰɣ�" << endl;
		}
		else if (guess < num) {
			cout << "���µ�����ƫС������һ�ΰɣ�" << endl;
		}
	}while (guess != num);
	cout << "���¶��ˣ���ȷ��������" << num << "����һ������" << count << "�Ρ�" << endl;
	return 0;
}