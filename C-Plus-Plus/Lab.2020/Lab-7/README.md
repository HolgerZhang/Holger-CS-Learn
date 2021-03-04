# C++实验报告

### 实验七 构造函数和析构函数

代码文件编码：UTF-8 (source code encoding)

本说明文档编码：UTF-8 (this file encoding)

### 一.   实验目的

通过本次实验要达到如下目的：

(1)	掌握C++语言的基础知识

(2)	熟悉C++语言的开发环境visual studio 2010

(3)	熟悉并掌握类的构造函数和析构函数。

(4)	掌握程序调试的基本技巧。

### 二.	实验内容

编写程序解决以下问题：

E01下面的一段程序中的Cline类中缺少了部分成员函数，该程序的运行结果如下：

~~~
Point 1 is:(0,0)
Point 2 is:(0,0)
Length=0
Point 1 is:(1,1)
Point 2 is:(5,5)
Length=5.65685
~~~

请为Cline函数补充必要的成员函数与实现代码，使得程序正确运行。

~~~c++
#include <iostream>
#include <cmath>
using namespace std;

class CPoint
{
	int m_x; //点的X坐标
	int m_y;	//点的Y坐标º
public:
	CPoint()
	{
		m_x=0;
		m_y=0;
	}
	CPoint (int x,int y)
	{
		m_x=x;
		m_y=y;
	}
	int getx()
	{
		return m_x;
	}
	int gety()
	{
		return m_y;
	}
	void showPoint()
	{
		cout<<"("<<this->m_x<<","<<this->m_y<<")"<<endl;
	}
};

class CLine
{
	CPoint m_point1;
	CPoint m_point2;
};

void main()
{
	CLine line1;
	line1.ShowLine();
	cout<<"Length="<<line1.distance()<<endl;

	CLine line2(1,1,5,5);
	line2.ShowLine();
	cout<<"Length="<<line2.distance()<<endl;
}
~~~

E02设有类CTime和CDate分别用于描述时间和日期，另外有CDateTime类描日期和时间，请为三个类给出具体的实现代码，并在main函数中测试。

~~~c++
#include <iostream>
#include <cmath>
using namespace std;

class CTime
{
	int m_hour,m_mintue,m_second;
public:
	CTime(int hour=0,int minute=0,int second=0);
	//如果时间合法，则赋值，否则赋值0时0分0秒
	int SetTime(int hour=0,int minute=0,int second=0);
	//如果时间合法，则赋值并返回1，否则不赋值，并返回0
	int getHour();
	int getMinute();
	int getSecond();
	void ShowTime(bool flag);
	//flag为True则以24小时制显示时间，否则以 AM PM的方式显示
	//自己考虑是否需要添加其他成员函数
};

class CDate
{
	int m_year,m_month,m_day;
public:
	CDate(int year=2000,int month=1,int day=1);
	//如果日期合法，则赋值，否则赋值2000年1月1日
	int SetDate(int year=2000,int month=1,int day=1);
	//如果日期合法，则赋值并返回1，否则不赋值，并返回0
	int GetYear();
	int GetMonth();
	int GetDay();
	void ShowDate(bool flag);
	//flag为TRUE，则以中文的方式显示日期，否则以MM/DD/YYYY的方式显示日期
	//自己考虑是否需要添加其他成员函数
};

class CDateTime
{
	CTime m_time;
	CDate m_date;
public:
	//添加必要的构造函数
	//int SetDateTime(...); 自己设计参数，考虑该函数的返回值加以表示全部正确、日期不对、时间不对等情况
	//void ShowDateTime(...); 自己设计参数，考虑可以中文日期和西文日期格式，以及24小时和AM PM都可以控制
	//添加自己认为必要的其他成员函数
};
~~~

在主函数中验证上述类的功能，要求的主函数如下所示，不允许进行修改：

~~~c++
void main()
{
	CDateTime d1(2014, 5, 2, 27, 12, 5);
	d1.ShowDateTime(false, true);		//第1个参数表示以英文方式显示日期, 第2个参数表示以24小时制方式显示时间

	CDateTime d2;
	d2.ShowDateTime(true, false);		//第1个参数表示以中文方式显示日期, 第2个参数表示以AM PM的方式显示时间

	int iStatus;
	iStatus=d2.SetDateTime(2014, 5, 2, 21, 55, 5);
	switch(iStatus)
	{
	case 1:
		cout<<"日期和时间数据设置正确!"<<endl;
		break;
	case -1:
		cout<<"日期数据设置不正确!"<<endl;
		break;
	case -2:
		cout<<"时间数据设置不正确!"<<endl;
		break;
	}
	d2.ShowDateTime(false, false);		//第1个参数表示以英文方式显示日期, 第2个参数表示以AM PM的方式显示时间

	cout<<"月="<<d2.GetMonth()<<endl;			//认真考虑一下如何实现此操作？
	cout<<"分钟="<<d2.GetMinute()<<endl;		//认真考虑一下如何实现此操作？
}
~~~