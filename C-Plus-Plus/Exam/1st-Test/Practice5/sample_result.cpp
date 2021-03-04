#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;


// �ṹ�嶨��

struct mark
{
	string xh;//ѧ��
	string kc;//�γ�����
	int    cj;//�ɼ�
};

struct student
{
	string xh;		//ѧ��
	int	math;		//��ѧ�ɼ�
	int english;		//Ӣ��ɼ�
	int cplusplus;	//C++�ɼ�
};


// ��������
int ReadFile(const char* filename, vector<struct mark>& marks);
void ShowData(const vector<struct mark>& marks, unsigned number = 3);
int Filter(vector<struct mark>& marks);
vector<struct student> FillData(const vector<struct mark>& marks);
template <class _Ranit,  class _Pr>
void SortData(const _Ranit first, const _Ranit last, _Pr pred);	// �޸�ǰ��SortData
void SortData(vector<struct student>& stus);	// �޸ĺ��SortData
bool cmp(const struct student& left, const struct student& right);
void ShowData(const vector<struct student>& stus, unsigned number);
void WriteFile(const char* filename, const vector<struct student>& stus);


// main��������
int main()
{
	vector <struct mark> marks;

	ReadFile("d:\\input.txt", marks); //��ȡ�ļ������ݵ�marks

	cout << "����������Ϊ��" << marks.size() << endl; //��ʾ��������
	ShowData(marks, 5);

	int count = Filter(marks);//ɾ�����в��Ϸ�������
	cout << "�ϼ�ɾ����" << count << "�����Ϸ��ɼ�" << endl;

	vector<struct student> stus = FillData(marks);
	cout << "���ܽ���ϼ���" << stus.size() << "��" << endl;

	//SortData(stus.begin(), stus.end(), cmp);
	SortData(stus); // �޸ĺ�

	cout << "�ܷ���͵�5����ϢΪ" << endl;
	ShowData(stus, 5);

	WriteFile("d:\\res.txt", stus);

	return 0;
}

int ReadFile(const char* filename, vector<struct mark>& marks) {
	ifstream fin(filename);	// ���ļ�
	if (!fin) {	// ����ļ��Ƿ�򿪳ɹ�
		//cout << "��ȡ�ļ�ʧ��";
		return -1;
	}
	while (!fin.eof()) {
		string xh, kc;	// ѧ�ţ��γ�����
		int    cj;		// �ɼ�
		fin >> xh >> kc >> cj;	// ��ȡ����
		if (xh == string()) {	// ����ļ��г��ֿ��е�����
			continue;
		}
		marks.push_back({ xh,kc,cj });	// ��������
	}
	fin.close();				// �ر��ļ�
	return 0;
}

void ShowData(const vector<struct mark>& marks, unsigned number) {
	unsigned end = min(marks.size(), number);
	for (unsigned i = 0; i < end; i++) {
		cout << setw(15) << setiosflags(ios::left) << marks[i].xh;	// ѧ��
		cout << setw(10) << setiosflags(ios::left) << marks[i].kc;	// �γ�����
		cout << setw(8) << setiosflags(ios::right) << marks[i].cj;	// �ɼ�
		cout << resetiosflags(ios::left | ios::right) << endl;
	}
}

int Filter(vector<struct mark>& marks) {
	int number = 0;
	// ʹ�õ�����ɾ�����Ϸ�������
	vector<struct mark>::iterator iter = marks.begin();
	while (iter != marks.end()) {
		if (iter->cj < 0 || iter->cj > 100) {
			iter = marks.erase(iter);
			number++;
		}
		else {
			++iter;
		}
	}
	return number;
}

vector<struct student> FillData(const vector<struct mark>& marks) {
	vector<struct student> res;	// ������
	for (unsigned i = 0; i < marks.size(); i++) {
		unsigned stuPos = 0;		// ѧ��Ϊmarks[i].xh��ѧ�����±�
		bool found = false;		// �Ƿ��ҵ���ѧ��
		for (stuPos = 0; stuPos < res.size(); stuPos++) {
			if (res[stuPos].xh == marks[i].xh) {
				found = true;
				break;
			}
		}
		if (!found) {		// δ�ҵ�������һ��ѧ���ṹ��
			res.push_back({ marks[i].xh,0,0,0 });	// �ɼ���ʼ����Ϊ0
			stuPos = res.size() - 1;
		}
		// ���ݿ�Ŀ����ɼ�
		string subject = marks[i].kc;
		if (subject == string("Math"))
			res[stuPos].math = marks[i].cj;
		else if (subject == string("English"))
			res[stuPos].english = marks[i].cj;
		else if (subject == string("C++"))
			res[stuPos].cplusplus = marks[i].cj;
	}
	return res;
}

// �޸�ǰ��SortData
template <class _Ranit, class _Pr>
void SortData(const _Ranit first, const _Ranit last, _Pr pred) {
	sort(first, last, pred);
}

// �޸ĺ��SortData
void SortData(vector<struct student>& stus) {
	sort(stus.begin(), stus.end(), cmp);
}

bool cmp(const struct student& left, const struct student& right) {
	// �����ܳɼ�
	int sumLeft = left.math + left.english + left.cplusplus;
	int sumRight = right.math + right.english + right.cplusplus;
	if (sumLeft==sumRight) {		// �ܷ���ͬʱ������ѧ�Ŵ�С��������
		return (left.xh < right.xh);
	}
	// �ִܷӸߵ�������
	return (sumLeft > sumRight);
}

void ShowData(const vector<struct student>& stus, unsigned number) {
	for (unsigned i = (stus.size()<=number ? 0u : stus.size()-number); i < stus.size(); i++) {
		cout << setw(15) << setiosflags(ios::left) << stus[i].xh;	// ѧ��
		cout << setw(5) << setiosflags(ios::right) << stus[i].math;		// math
		cout << setw(5) << setiosflags(ios::right) << stus[i].english;	// en
		cout << setw(5) << setiosflags(ios::right) << stus[i].cplusplus;	// cpp
		cout << resetiosflags(ios::left | ios::right) << endl;
	}
}

void WriteFile(const char* filename, const vector<struct student>& stus) {
	ofstream fout(filename);		// ���ļ�
	for (unsigned i = 0; i < stus.size(); i++) {
		fout << setw(15) << setiosflags(ios::left) << stus[i].xh;	// ѧ��
		fout << setw(5) << setiosflags(ios::right) << stus[i].math;		// math
		fout << setw(5) << setiosflags(ios::right) << stus[i].english;	// en
		fout << setw(5) << setiosflags(ios::right) << stus[i].cplusplus;	// cpp
		fout << resetiosflags(ios::left | ios::right) << endl;
	}
	fout.close();					// �ر��ļ�
}
