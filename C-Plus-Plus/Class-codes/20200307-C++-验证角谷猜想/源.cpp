//�ǹȲ���
#include<iostream>
using namespace std;

int main()
{
	int num = 0, cnt = 0;
	cout << "������һ����������";
	cin >> num;
	while (num != 1) {
		cnt++;
		int last = num;
		switch (num % 2) {
		case 0:	//ż��
			num /= 2;
			cout << last << "/2=" << num << endl;
			break;
		case 1:	//����
			num = 3 * last + 1;
			cout << "3*" << last << "+1=" << num << endl;
			break;
		}
	}
	cout << "��������" << cnt << "��" << endl;
	return 0;
}