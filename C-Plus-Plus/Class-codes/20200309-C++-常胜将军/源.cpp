//��ʤ����
#include<iostream>
using namespace std;

int main()
{
	int coins = 21;
	do {
		int PersonGet, ComputerGet;
		while (1) {
			cout << "������" << coins << "öӲ�ҡ�";
			cout << "��������Ҫȡ��Ӳ�ҵ�������1-4ö����";
			cin >> PersonGet;
			if (PersonGet >= 1 && PersonGet <= 4 && PersonGet <= coins)
				break;
			cout << "��ȡ�ߵ������ǲ��Ϸ��ģ����������롣" << endl;
		}
		ComputerGet = 5 - PersonGet;
		coins -= ComputerGet+ PersonGet;
		cout << "����ȡ����" << ComputerGet << "öӲ�ҡ�" << endl;
	} while (coins != 1);
	cout << "�����ˣ���ֻ��ȡ����һöӲ�ҡ�" << endl;
	return 0;
}