#include <iostream>
using namespace std;


class MyClock
{
private:
	int m_hour = 0, m_minute = 0, m_second = 0;
public:
	MyClock();
	MyClock(int h, int m, int s);
	void show() const;
	void setTime(int h, int m, int s);
	int setHour(int h);
	int getHour() const;
	int setMinute(int m);
	int getMinute() const;
	int setSecond(int s);
	int getSecond() const;
};

MyClock::MyClock()
{
	m_hour = 0;
	m_minute = 0;
	m_second = 0;
}

MyClock::MyClock(int h, int m, int s)
{
	setHour(h);
	setMinute(m);
	setSecond(s);
}

void MyClock::show() const
{
	cout << m_hour << ":" << m_minute << ":" << m_second;
}

void MyClock::setTime(int h, int m, int s)
{
	setHour(h);
	setMinute(m);
	setSecond(s);
}

int MyClock::setHour(int h)
{
	if (h < 0 || h > 23) {
		return -1;
	}
	m_hour = h;
	return 0;
}

int MyClock::getHour() const
{
	return m_hour;
}

int MyClock::setMinute(int m)
{
	if (m < 0 || m >= 60) {
		return -1;
	}
	m_minute = m;
	return 0;
}

int MyClock::getMinute() const
{
	return m_minute;
}

int MyClock::setSecond(int s)
{
	if (s < 0 || s >= 60) {
		return -1;
	}
	m_second = s;
	return 0;
}

int MyClock::getSecond() const
{
	return m_second;
}

int main()
{
	MyClock clock;
//	clock.setTime(12, 35, 27);
	clock.show();
	return 0;
}
