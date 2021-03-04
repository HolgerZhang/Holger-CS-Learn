/*******************************************
	学号：
	姓名：
	手机号码：
*******************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class CWorker
{
private:
	int m_ID;		//工号
	string m_Name;	//姓名
	int m_Sex;		//性别	0代表女性	1代表男性
	int m_Age;		//年龄

public:
	CWorker(int ID, string Name, int Sex, int Age)
	{
		if (Sex<0 || Sex>1)
		{
			cout<<"性别初始值"<<Sex<<"不符合要求！"<<endl;
			exit(0);
		}
		if (Age<=0 )
		{
			cout<<"年龄初始值"<<Age<<"不符合要求！"<<endl;
			exit(0);
		}

		m_ID=ID;
		m_Name=Name;
		m_Sex=Sex;
		m_Age=Age;
	}

	string GetName()const
	{
		return m_Name;
	}

	int GetSex()const
	{
		return m_Sex;
	}

	int GetAge()const
	{
		return m_Age;
	}

	friend ostream& operator<<(ostream& Out, const CWorker& Obj)
	{
		Out<<right<<setw(5)<<Obj.m_ID;
		Out<<right<<setw(10)<<Obj.m_Name;
		Out<<right<<setw(5)<<Obj.m_Sex;
		Out<<right<<setw(6)<<Obj.m_Age;

		return Out;
	}
};



int main()
{
	vector<CBenchWorker> a;
	int c;

	if (ReadData("d:\\workers.txt", a)==0)
		return -1;
	
	cout<<"文件读取后一共有 "<<a.size()<<" 条钳工数据："<<endl;
	DisplayData(a);

	InecData(a);

	c=DelData(a,55,2);	//第2个参数为年龄，第3个参数为等级
	cout<<endl<<"第1次删除了"<<c<<"个钳工数据"<<endl;

	c=DelData(a,"Tom");
	cout<<endl<<"第2次删除了"<<c<<"个钳工数据"<<endl;

	SortData(a);

	cout<<endl<<"上述流程结束后一共有 "<<a.size()<<" 条钳工数据："<<endl;
	DisplayData(a);

	if (WriteData("d:\\res.txt",a)==0)
		return -1;
	cout<<endl<<"文件保存成功"<<endl<<endl;
}