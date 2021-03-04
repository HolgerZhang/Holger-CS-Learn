#include <iostream>
using namespace std;

class Birthday
{
private:
	int year;	// ��
	int month;	// ��
	int day;		// ��
	// �ж������Ƿ�Ϸ�
	bool IsValid(int y, int m, int d)
	{
		// �ж������
		if (y < 0 || (m < 1 || m > 12))
			return false;
		int eachMonthDay[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		// �ж��Ƿ�������Ķ���
		if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0))
			eachMonthDay[1]++;
		// �ж���
		if (d<1 || d>eachMonthDay[m - 1])
			return false;
		return true;
	}

public:
	void setValue(int y, int m, int d)
	{
		if (!IsValid(y, m, d)) {
			return;
		}
		year = y;
		month = m;
		day = d;
	}
	// ��ʾ����
	void show()
	{
		cout << year << '-' << month << '-' << day;
	}
};


int main()
{
	Birthday day1;
	day1.setValue(2020, 4, 23);
	day1.show();
	return 0;
}