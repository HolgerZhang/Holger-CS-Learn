/*******************************************
	ѧ�ţ�
	������
	�ֻ����룺
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
	int m_ID;		//����
	string m_Name;	//����
	int m_Sex;		//�Ա�	0����Ů��	1��������
	int m_Age;		//����

public:
	CWorker(int ID, string Name, int Sex, int Age)
	{
		if (Sex<0 || Sex>1)
		{
			cout<<"�Ա��ʼֵ"<<Sex<<"������Ҫ��"<<endl;
			exit(0);
		}
		if (Age<=0 )
		{
			cout<<"�����ʼֵ"<<Age<<"������Ҫ��"<<endl;
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
	
	cout<<"�ļ���ȡ��һ���� "<<a.size()<<" ��ǯ�����ݣ�"<<endl;
	DisplayData(a);

	InecData(a);

	c=DelData(a,55,2);	//��2������Ϊ���䣬��3������Ϊ�ȼ�
	cout<<endl<<"��1��ɾ����"<<c<<"��ǯ������"<<endl;

	c=DelData(a,"Tom");
	cout<<endl<<"��2��ɾ����"<<c<<"��ǯ������"<<endl;

	SortData(a);

	cout<<endl<<"�������̽�����һ���� "<<a.size()<<" ��ǯ�����ݣ�"<<endl;
	DisplayData(a);

	if (WriteData("d:\\res.txt",a)==0)
		return -1;
	cout<<endl<<"�ļ�����ɹ�"<<endl<<endl;
}