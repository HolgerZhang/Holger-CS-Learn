#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    cout << "��ʼ" << endl;
	try {
		cout << "����try����." << endl;
		throw 200;
		cout << "���ᱻִ��" << endl;
	}
	catch (int i) {
		cout << "����һ���쳣������ֵΪ��" << i << endl;
	}
	cout << "����" << endl;
	return 0;
}
