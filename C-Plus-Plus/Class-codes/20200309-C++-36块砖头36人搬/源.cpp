//36��שͷ36�˰�, ���ˣ�4��, Ů�ˣ�2��, С����2�˰�1��
#include<iostream>
using namespace std;

int main()
{
	int male, female, child;
	for (male = 0; male <= 9; male++) {
		for (female = 0; female <= 18; female++) {
			child = 36 - male - female;
			if (4 * male + 2 * female + child*0.5 ==36) {
				cout << male << "���ˣ�" << female << "Ů�ˣ�" << child << "С����" << endl;
			}
		}
	}
	return 0;
}