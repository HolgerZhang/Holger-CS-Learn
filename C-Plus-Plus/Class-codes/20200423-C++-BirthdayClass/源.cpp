#include <iostream>
using namespace std;

class Birthday
{
private:
	int year;	// 年
	int month;	// 月
	int day;		// 日
	// 判断日期是否合法
	bool IsValid(int y, int m, int d)
	{
		// 判断年和月
		if (y < 0 || (m < 1 || m > 12))
			return false;
		int eachMonthDay[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		// 判断是否是闰年的二月
		if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0))
			eachMonthDay[1]++;
		// 判断日
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
	// 显示日期
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