/* 2016 test 3th */
#include <iostream>
#include <iomanip>

using namespace std;

class Time {
protected:
    int m_hour, m_minute, m_second;    //m_hour 值可正可负，详见说明。
public:
    Time(int hour = 0, int minute = 0,
         int second = 0);    // 构造函数
    void set(int hour = 0, int minute = 0, int second = 0);    //设置时间
    Time operator-(const Time &tm);    //计算时间差，可正可负
    friend ostream &operator<<(ostream &os, const Time &tm); //流输出运算符
};

Time::Time(int hour, int minute, int second) {
    // if ((hour < -23) || (hour > 23)) {
    //     cout << "hour 值错误" << endl;
    //     exit(0);
    // }
    if ((minute < 0) || (minute > 59)) minute = 0;
    if ((second < 0) || (second > 59))

        second = 0;
    m_hour = hour;
    m_minute = minute;
    m_second = second;
}

void Time::set(int hour, int minute, int second) {
    // if ((hour < -23) || (hour > 23)) {
    //     cout << "hour 值错误" << endl;
    //     exit(0);
    // }
    if ((minute < 0) || (minute > 59)) minute = 0;
    if ((second < 0) || (second > 59)) second = 0;
    m_hour = hour;
    m_minute = minute;
    m_second = second;
}

Time Time::operator-(const Time &tm) {    //计算时间差，可正可负
    int now, next;
    now = m_hour * 3600 + m_minute * 60 + m_second;
    next = tm.m_hour * 3600 + tm.m_minute * 60 + tm.m_second;
    if (now >= next) {
        return Time(
                (now - next) / 3600, ((now - next) % 3600) / 60, (now - next) % 60);
    }
    return Time(
            ((now - next) / 3600), ((next - now) % 3600) / 60, (next - now) % 60);
}

ostream &operator<<(ostream &os, const Time &tm) {    //流输出运算符
    int value = tm.m_hour;
    if (tm.m_hour < 0) {
        os << "-";
        value = -value;
    }
    os << setw(2) << setfill('0') << value
       << ":" << setw(2) << setfill('0') << tm.m_minute
       << ":" << setw(2) << setfill('0') << tm.m_second;
    return os;
}

class WorldTime : public Time {
    int m_timezone;
public:
    WorldTime(int timezone, int hour, int minute, int second)
            : Time(hour, minute, second), m_timezone(timezone) {}

    WorldTime(const WorldTime &k)
            : Time(k.m_hour, k.m_minute, 0), m_timezone(k.m_timezone) {}

    Time operator-(const WorldTime &tm) {
        // 要确定是转到哪个时区去计算差：转到 tm 所在时区计算时间差。
        int now, next;
        now = (m_hour - m_timezone) * 3600 + m_minute * 60 + m_second;
        next = (tm.m_hour - tm.m_timezone) * 3600 + tm.m_minute * 60 + tm.m_second;
        if (now >= next) {
            return Time(
                    (now - next) / 3600, ((now - next) % 3600) / 60, (now - next) % 60);
        }
        return Time(
                ((now - next) / 3600), ((next - now) % 3600) / 60, (next - now) % 60);
    }

    WorldTime operator++(int) {
        WorldTime k(*this);
        if (++m_timezone > 12) m_timezone = -12;
        return k;
    }

    void convert(int k) {
        if (k < -12 || k > 12) k = 0;
        m_hour += (k - m_timezone);
        m_timezone = k;
        if (m_hour < 0)m_hour += 24;
        if (m_hour > 24)m_hour -= 24;
    }

    friend ostream &operator<<(ostream &os, const WorldTime &tm);
};

ostream &operator<<(ostream &os, const WorldTime &tm) {
    os << "[";
    if (tm.m_timezone >= 0)os << "+" << setw(2) << setfill('0') << tm.m_timezone;
    else
        os << "-" << setw(2) << setfill('0') << -tm.m_timezone;
    os << "] ";
    os << static_cast<const Time &>(tm);
    return os;
}

int main() {
    cout << "----------Section 1----------" << endl;
    Time tm1(8, 12, 153), tm2;
    cout << tm1 << endl;
    cout << tm2 << endl;
    cout << tm2 - tm1 << endl;
    cout << "----------Section 2----------" << endl;
    WorldTime wtm1(12, 7, 14, 29), wtm2(-10, 23, 10, 9), wtm3(wtm2);
    cout << wtm1 << endl;
    cout << wtm2 << endl;
    cout << wtm3 << endl;
    cout << wtm2 - wtm1 << endl;
    cout << "----------Section 3----------" << endl;

    wtm1++;
    cout << wtm1 << endl;
    wtm2.convert(20);
    wtm3.convert(8);
    cout << wtm2 << endl;
    cout << wtm3 << endl;
    cout << "----------Finish-------------" << endl;
    return 0;
}

