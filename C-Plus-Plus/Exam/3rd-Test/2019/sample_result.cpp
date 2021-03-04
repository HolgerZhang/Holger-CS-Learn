#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

// 此处为CPerson类的代码，不得修改
class CPerson
{
protected:
	string		m_name;					//姓名
	int			m_age;					//年龄
	string		m_gender;				//性别
public:
	CPerson(string name, int age, string gender)		//构造函数
	{
		m_name		= name;
		m_age		= age;
		m_gender	= gender;
	}
	string getName() const				//获取姓名
	{
		return m_name;
	}
	int getAge() const					//获取年龄
	{
		return m_age;
	}
	string getGender() const			//获取性别
	{
		return m_gender;
	}
};

// 此处插入CTeacher类的代码和所需的其它代码


// 此处插入readData函数


// 此处插入showData函数


// 此处插入processData函数


// 以下部分为main函数，不得修改
void main()
{
	vector<CTeacher> myVect;			//创建向量
	readData("teacher.txt", myVect);	//从文件中读取数据到向量
	showData(myVect);					//显示读取到的数据
	vector<CTeacher> myVectNew;			//创建向量
	processData(myVect, myVectNew);		//将myVect中的对象按要求添加到myVectNew中
	showData(myVectNew);				//显示myVectNew向量中的对象
	return;
}
