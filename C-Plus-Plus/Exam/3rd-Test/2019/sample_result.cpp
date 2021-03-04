#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

// �˴�ΪCPerson��Ĵ��룬�����޸�
class CPerson
{
protected:
	string		m_name;					//����
	int			m_age;					//����
	string		m_gender;				//�Ա�
public:
	CPerson(string name, int age, string gender)		//���캯��
	{
		m_name		= name;
		m_age		= age;
		m_gender	= gender;
	}
	string getName() const				//��ȡ����
	{
		return m_name;
	}
	int getAge() const					//��ȡ����
	{
		return m_age;
	}
	string getGender() const			//��ȡ�Ա�
	{
		return m_gender;
	}
};

// �˴�����CTeacher��Ĵ�����������������


// �˴�����readData����


// �˴�����showData����


// �˴�����processData����


// ���²���Ϊmain�����������޸�
void main()
{
	vector<CTeacher> myVect;			//��������
	readData("teacher.txt", myVect);	//���ļ��ж�ȡ���ݵ�����
	showData(myVect);					//��ʾ��ȡ��������
	vector<CTeacher> myVectNew;			//��������
	processData(myVect, myVectNew);		//��myVect�еĶ���Ҫ����ӵ�myVectNew��
	showData(myVectNew);				//��ʾmyVectNew�����еĶ���
	return;
}
