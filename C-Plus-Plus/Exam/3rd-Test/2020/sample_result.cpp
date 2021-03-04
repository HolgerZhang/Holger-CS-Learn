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
		if (Sex < 0 || Sex > 1)
		{
			cout << "�Ա��ʼֵ" << Sex << "������Ҫ��" << endl;
			exit(0);
		}
		if (Age <= 0)
		{
			cout << "�����ʼֵ" << Age << "������Ҫ��" << endl;
			exit(0);
		}

		m_ID = ID;
		m_Name = Name;
		m_Sex = Sex;
		m_Age = Age;
	}

	string GetName() const
	{
		return m_Name;
	}

	int GetSex() const
	{
		return m_Sex;
	}

	int GetAge() const
	{
		return m_Age;
	}

	friend ostream& operator<<(ostream& Out, const CWorker& Obj)
	{
		Out << right << setw(5) << Obj.m_ID;
		Out << right << setw(10) << Obj.m_Name;
		Out << right << setw(5) << Obj.m_Sex;
		Out << right << setw(6) << Obj.m_Age;

		return Out;
	}
};

/*******************************************
 * @brief CBenchWorker�࣬��������ǯ��
 *******************************************/
class CBenchWorker : public CWorker {
private:
	int m_Grade; // ǯ������ 1-5�����Ϊ5��
public:
	/*******************************************
	 * @brief ���캯��
	 * @param ID ���ţ�Ĭ��ֵ0
	 * @param Name ������Ĭ��ֵ"No Name"
	 * @param Sex �Ա�Ĭ��ֵ���ԣ�1��
	 * @param Age ���䡣Ĭ��ֵ18
	 * @param Grade ǯ���ȼ���Ĭ��ֵ1
	 ******************************************/
	CBenchWorker(int ID = 0, string Name = "No Name", int Sex = 1, int Age = 18, int Grade = 1)
		: CWorker(ID, Name, Sex, Age) {
		if (Grade < 1 || Grade > 5) {  // �ж�ǯ�������Ƿ����Ҫ��
			cout << "ǯ�������ʼֵ" << Grade << "������Ҫ��" << endl;
			exit(0);
		}
		m_Grade = Grade;
	}

	/*******************************************
	 * @brief ���ؼ���ĳ�Ա����
	 * @return ǯ������
	 ******************************************/
	int GetGrade() const {
		return m_Grade;
	}

	/*******************************************
	 * @brief ǰ++����������ڽ�ǯ���ļ����1
	 * @return ������Ķ���
	 ******************************************/
	CBenchWorker& operator++() {
		m_Grade++;
		if (m_Grade < 1 || m_Grade > 5) {  // �ж�ǯ�������Ƿ����Ҫ��
			cout << "ǯ�������ʼֵ" << m_Grade << "������Ҫ��" << endl;
			exit(0);
		}
		return *this;
	}

	// ��������������<<����Ԫ����
	friend ostream& operator<<(ostream&, const CBenchWorker&);

};

/*******************************************
 * @brief ��������������<<����Ԫ����
 * @param out ����������
 * @param worker Ҫ�����ǯ������
 * @return ����������
 ******************************************/
ostream& operator<<(ostream& out, const CBenchWorker& worker) {
	out << (CWorker)worker;
	out << setw(5) << worker.m_Grade;
	return out;
}

/*******************************************
 * @brief �������ļ��ж�ȡ���ݣ�������ɶ��󲢴洢
 * @param file �����ļ�·��
 * @param myVect ��ǯ��������ɵĵ�����
 * @return 0-��ȡʧ�ܣ�1-��ȡ�ɹ�
 ******************************************/
int ReadData(const string& file, vector<CBenchWorker>& myVect) {
	ifstream inFile(file);
	if (!inFile) {  // ���Ƿ�ɹ�
		return 0;  // ��ȡʧ��
	}
	while (!inFile.eof()) {  // ��ȡ�ļ�
		int id, sex, age, grade;
		string name;
		inFile >> id >> name >> sex >> age >> grade;
		myVect.push_back(CBenchWorker(id, name, sex, age, grade));
	}
	inFile.close();  // �ر��ļ�
	return 1;  // ��ȡ�ɹ�
}

/*******************************************
 * @brief ��ʾ��Щǯ����Ϣ��ÿ��ǯ������ռһ��
 * @param myVect ǯ����Ϣ����
 ******************************************/
void DisplayData(const vector<CBenchWorker>& myVect) {
	for (auto& worker : myVect) {
		cout << worker << endl;
	}
}

/*******************************************
 * @brief ������ǯ������ִ��ǰ��������
 *         �����Ȼ������myVect��
 * @param myVect ǯ����Ϣ����
 ******************************************/
void InecData(vector<CBenchWorker>& myVect) {
	for (auto& worker : myVect) {
		++worker;
	}
}

/**************************************************
 * @brief ɾ������������ڵ���X���Ҽ���С�ڵ���Y����ǯ��
 *         �����Ȼ������myVect�У�������ɾ������
 * @param myVect ǯ����Ϣ����
 * @param ageX ��������
 * @param gradeY �ȼ�����
 * @return ɾ������
 *************************************************/
int DelData(vector<CBenchWorker>& myVect, int ageX, int gradeY) {
	int number = 0;  // ɾ������
	auto iter = myVect.begin();
	while (iter != myVect.end()) {  // ����ɾ��
		if (iter->GetAge() >= ageX && iter->GetGrade() <= gradeY) {  // ��������ɾ��
			iter = myVect.erase(iter);
			number++;
		}
		else {  // ��������������������
			++iter;
		}
	}
	return number;
}

/*******************************************
 * @brief תСд����
 * @param word �ַ���
 * @return Сд���ַ���
 ******************************************/
string lowerCase(const string& word) {
	string newWord(word);
	for (char& ch : newWord) {
		if (ch >= 'A' && ch <= 'Z') {
			ch += 32;
		}
	}
	return newWord;
}

/***************************************************
 * @brief ɾ�����������а�������Сд�����У��ַ���X��ǯ��
 *         �����Ȼ������myVect �У�������ɾ��������
 * @param myVect ǯ����Ϣ����
 * @param strX ����Сд�����У��������ַ���
 * @return ɾ������
 **************************************************/
int DelData(vector<CBenchWorker>& myVect, const string& strX) {
	int number = 0;  // ɾ������
	string contain = lowerCase(strX);  // �ַ���XתСд
	auto iter = myVect.begin();
	while (iter != myVect.end()) {  // ����ɾ��
		string name = lowerCase(iter->GetName());  // ǯ������תСд
		if (name.find(contain) != string::npos) {  // ������ɾ��
			iter = myVect.erase(iter);
			number++;
		}
		else {  // ����������������
			++iter;
		}
	}
	return number;
}

/*******************************************
 * @brief �����������Ƚ�����ǯ������
 * @param left �������
 * @param right �Ҳ�����
 * @return true - left < right
 *          false - !(left < right)
 ******************************************/
bool cmpCBenchWorkerObj(const CBenchWorker& left, const CBenchWorker& right) {
	if (left.GetSex() == right.GetSex()) {  // �Ա���ͬ
		switch (left.GetSex()) {
		case 0:  // Ů�� ������
			return (left.GetGrade() > right.GetGrade());
		case 1: // ���� ��������
			return (left.GetGrade() < right.GetGrade());
		}
	}
	return (left.GetSex() < right.GetSex());  // Ůʿ����
}

/*************************************************************
 * @brief ������ǯ�������Ա�Ůʿ���ȣ�Ů����ǰ�������ں󣩽�������
 *        ����ǯ���а��ռ�������������У�Ů��ǯ���а��ռ�����н�������
 * @param myVect Ҫ�����ǯ������
 *************************************************************/
void SortData(vector<CBenchWorker>& myVect) {
	sort(myVect.begin(), myVect.end(), cmpCBenchWorkerObj);
}

/*******************************************
 * @brief ��ǯ����Ϣ���浽ָ���ļ���
 *         ÿ��ǯ������ռһ��
 * @param file �����ļ�·��
 * @param myVect ��ǯ��������ɵĵ�����
 * @return 0-����ʧ�ܣ�1-����ɹ�
 ******************************************/
int WriteData(const string& file, const vector<CBenchWorker>& myVect) {
	ofstream outFile(file);
	if (!outFile) {  // ���Ƿ�ɹ�
		return 0;  // ����ʧ��
	}
	for (auto& worker : myVect) {  // д���ļ�
		outFile << worker << endl;
	}
	outFile.close();  // �ر��ļ�
	return 1;  // ����ɹ�

}

// ����������
int main() {
	vector<CBenchWorker> a;
	int c;

	if (ReadData("d:\\workers.txt", a) == 0)
		return -1;

	cout << "�ļ���ȡ��һ���� " << a.size() << " ��ǯ�����ݣ�" << endl;
	DisplayData(a);

	InecData(a);

	c = DelData(a, 55, 2);	//��2������Ϊ���䣬��3������Ϊ�ȼ�
	cout << endl << "��1��ɾ����" << c << "��ǯ������" << endl;

	c = DelData(a, "Tom");
	cout << endl << "��2��ɾ����" << c << "��ǯ������" << endl;

	SortData(a);

	cout << endl << "�������̽�����һ���� " << a.size() << " ��ǯ�����ݣ�" << endl;
	DisplayData(a);

	if (WriteData("d:\\res.txt", a) == 0)
		return -1;
	cout << endl << "�ļ�����ɹ�" << endl << endl;
}
