/**
 * @file E02.cpp
 * @create 2020-06-28 22:08
 * @encoding UTF-8
 * @author Holger
 * @description 设有类CTime和CDate分别用于描述时间和日期，另外有CDateTime类描日期和时间，请为三个类给出具体的实现代码，并在main函数中测试。
 **/

#include <iostream>
#include <iomanip>

using namespace std;

class CTime {
    int m_hour, m_minute, m_second;
public:
    //如果时间合法，则赋值，否则赋值0时0分0秒
    CTime(int hour = 0, int minute = 0, int second = 0);

    //如果时间合法，则赋值并返回1，否则不赋值，并返回0
    int SetTime(int hour = 0, int minute = 0, int second = 0);

    int getHour();

    int getMinute();

    int getSecond();

    //flag为True则以24小时制显示时间，否则以 AM PM的方式显示
    void ShowTime(bool flag);

    static bool isValidTime(int hour, int minute, int second);
};

class CDate {
    int m_year, m_month, m_day;
public:
    //如果日期合法，则赋值，否则赋值2000年1月1日
    CDate(int year = 2000, int month = 1, int day = 1);

    //如果日期合法，则赋值并返回1，否则不赋值，并返回0
    int SetDate(int year = 2000, int month = 1, int day = 1);

    int GetYear();

    int GetMonth();

    int GetDay();

    //flag为TRUE，则以中文的方式显示日期，否则以MM/DD/YYYY的方式显示日期
    void ShowDate(bool flag);

    static bool isValidDate(int year, int month, int day);

private:
    static const int DAYS_IN_MONTH[12];  // 每个月天数

    static bool isLeapYear(int year);
};

class CDateTime {
    CTime m_time;
    CDate m_date;
public:
    CDateTime();

    CDateTime(int year, int month, int day, int hour, int minute, int second);

    int SetDateTime(int year = 2000, int month = 1, int day = 1, int hour = 0, int minute = 0, int second = 0);

    void ShowDateTime(bool dateFlag, bool timeFlag);

    int GetMonth();

    int GetMinute();
};


/**
 * CTime 构造函数
 * 如果时间合法，则赋值，否则赋值0时0分0秒
 * @param hour 小时
 * @param minute 分钟
 * @param second 秒
 */
CTime::CTime(int hour, int minute, int second) {
    if (!isValidTime(hour, minute, second)) {
        hour = 0;
        minute = 0;
        second = 0;
    }
    m_hour = hour;
    m_minute = minute;
    m_second = second;
}

/**
 * 设定时间
 * 如果时间合法，则赋值并返回1，否则不赋值，并返回0
 * @param hour 小时
 * @param minute 分钟
 * @param second 秒
 * @return 1 - 时间合法并且成功赋值; 0 - 时间不合法，不赋值
 */
int CTime::SetTime(int hour, int minute, int second) {
    if (!isValidTime(hour, minute, second)) {
        return 0;
    }
    m_hour = hour;
    m_minute = minute;
    m_second = second;
    return 1;
}

/**
 * 获取小时
 * @return m_hour
 */
int CTime::getHour() {
    return m_hour;
}

/**
 * 获取分钟
 * @return m_minute
 */
int CTime::getMinute() {
    return m_minute;
}

/**
 * 获取秒
 * @return m_second
 */
int CTime::getSecond() {
    return m_second;
}

/**
 * 显示时间
 * @param flag 为True则以24小时制显示时间，否则以 AM PM的方式显示
 */
void CTime::ShowTime(bool flag) {
    int hour;
    if (flag) {
        hour = m_hour;
    } else {
        int am = (m_hour >= 12) ? 0 : 1;
        hour = m_hour % 12;
        if (hour == 0) hour = 12;
        cout << (am ? "AM" : "PM");
    }
    cout << setfill('0') << setiosflags(ios::right);
    cout << setw(2) << hour << ":" << setw(2) << m_minute << ":" << setw(2) << m_second;
    cout << resetiosflags(ios::right);
}

/**
 * 判断时间是否合法
 * @param year 年
 * @param month 月
 * @param day 日
 * @return true - 合法; false - 不合法
 */
bool CTime::isValidTime(int hour, int minute, int second) {
    return (hour >= 0 && hour < 24 && minute >= 0 && minute < 60 && second >= 0 && second < 60);
}

const int CDate::DAYS_IN_MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/**
 * CDate构造函数
 * 如果日期合法，则赋值，否则赋值2000年1月1日
 * @param year 年
 * @param month 月
 * @param day 日
 */
CDate::CDate(int year, int month, int day) {
    if (!isValidDate(year, month, day)) {
        year = 2000, month = 1, day = 1;
    }
    m_year = year;
    m_month = month;
    m_day = day;
}

/**
 * 判断日期是否合法
 * @param year 年
 * @param month 月
 * @param day 日
 * @return true - 合法; false - 不合法
 */
bool CDate::isValidDate(int year, int month, int day) {
    if (!(month >= 1 && month <= 12)) {
        return false;
    }
    int dayMax = DAYS_IN_MONTH[month - 1];
    if (month == 2 && isLeapYear(year)) {
        dayMax++;
    }
    return (day >= 1 && day <= dayMax);
}

/**
 * 判断时候为闰年
 * @param year 年
 * @return true - 是闰年; false - 不是闰年
 */
bool CDate::isLeapYear(int year) {
    return (year % 400 == 0 || year % 4 == 0 && year % 100 != 0);
}

/**
 * 设置日期
 * 如果日期合法，则赋值并返回1，否则不赋值，并返回0
 * @param year 年
 * @param month 月
 * @param day 日
 * @return 1 - 日期合法并且成功赋值; 0 - 日期不合法，不赋值
 */
int CDate::SetDate(int year, int month, int day) {
    if (!isValidDate(year, month, day)) {
        return 0;
    }
    m_year = year;
    m_month = month;
    m_day = day;
    return 1;
}

/**
 * 获取年
 * @return m_year
 */
int CDate::GetYear() {
    return m_year;
}

/**
 * 获取月
 * @return m_month
 */
int CDate::GetMonth() {
    return m_month;
}

/**
 * 获取日
 * @return m_day
 */
int CDate::GetDay() {
    return m_day;
}

/**
 * 显示日期
 * @param flag 为TRUE，则以中文的方式显示日期，否则以MM/DD/YYYY的方式显示日期
 */
void CDate::ShowDate(bool flag) {
    if (flag) {
        cout << m_year << "年" << m_month << "月" << m_day << "日";
    } else {
        cout << setfill('0') << setiosflags(ios::right);
        cout << setw(2) << m_month << "/" << setw(2) << m_day << "/" << setw(4) << m_year;
        cout << resetiosflags(ios::right);
    }
}

/**
 * CDateTime默认构造函数
 */
CDateTime::CDateTime() : m_date(), m_time() {}

/**
 * CDateTime构造函数
 * @param year 年
 * @param month 月
 * @param day 日
 * @param hour 小时
 * @param minute 分钟
 * @param second 秒
 */
CDateTime::CDateTime(int year, int month, int day, int hour, int minute, int second)
        : m_date(year, month, day), m_time(hour, minute, second) {}

/**
 * 设置日期时间
 * @param year 年
 * @param month 月
 * @param day 日
 * @param hour 小时
 * @param minute 分钟
 * @param second 秒
 * @return 0 - 日期和时间数据设置均不正确; 1 - 日期和时间数据设置正确; -1 - 日期数据设置不正确; -2 - 时间数据设置不正确
 */
int CDateTime::SetDateTime(int year, int month, int day, int hour, int minute, int second) {
    switch (m_date.SetDate(year, month, day) + (m_time.SetTime(hour, minute, second) << 1)) {
        case 0:  // 日期和时间数据设置均不正确
            return 0;
        case 1:  // 时间数据设置不正确
            return -2;
        case 2:  // 日期数据设置不正确
            return -1;
        case 3:  // 日期和时间数据设置正确
            return 1;
    }
}

/**
 * 显示日期时间
 * @param dateFlag 为TRUE，则以中文的方式显示日期，否则以MM/DD/YYYY的方式显示日期
 * @param timeFlag 为True则以24小时制显示时间，否则以 AM PM的方式显示
 */
void CDateTime::ShowDateTime(bool dateFlag, bool timeFlag) {
    m_date.ShowDate(dateFlag);
    cout << ' ';
    m_time.ShowTime(timeFlag);
    cout << endl;
}

/**
 * 获取月
 * @return m_date.m_month
 */
int CDateTime::GetMonth() {
    return m_date.GetMonth();
}

/**
 * 获取分钟
 * @return m_time.m_minute
 */
int CDateTime::GetMinute() {
    return m_time.getMinute();
}


int main() {
    CDateTime d1(2014, 5, 2, 27, 12, 5);
    d1.ShowDateTime(false, true);        //第1个参数表示以英文方式显示日期, 第2个参数表示以24小时制方式显示时间

    CDateTime d2;
    d2.ShowDateTime(true, false);        //第1个参数表示以中文方式显示日期, 第2个参数表示以AM PM的方式显示时间

    int iStatus;
    iStatus = d2.SetDateTime(2014, 5, 2, 21, 55, 5);
    switch (iStatus) {
        case 1:
            cout << "日期和时间数据设置正确!" << endl;
            break;
        case -1:
            cout << "日期数据设置不正确!" << endl;
            break;
        case -2:
            cout << "时间数据设置不正确!" << endl;
            break;
    }
    d2.ShowDateTime(false, false);        //第1个参数表示以英文方式显示日期, 第2个参数表示以AM PM的方式显示时间

    cout << "月=" << d2.GetMonth() << endl;            //认真考虑一下如何实现此操作？
    cout << "分钟=" << d2.GetMinute() << endl;        //认真考虑一下如何实现此操作？
}