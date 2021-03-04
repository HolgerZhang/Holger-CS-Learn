#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ������Ϣ�Ľṹ����������
typedef struct {
	int ID;				//����
	string Name;			//����
	int WorkYears;		//����
	float Salary;		//����
} WORKER;

// ��������
int readData(const string& filePath, vector<WORKER>& workerVector);
void Sort(vector<WORKER>& Arr);
void Display(const vector<WORKER>& workerVector);
void Fliter(const vector<WORKER>& workerVectorA, vector<WORKER>& workerVectorB, int X = 10);
vector<WORKER> Fliter(const vector<WORKER>& workerVector, double Y = 1500.0);

// ������
int main() {
	string filePath = "d:\\input.txt";
	vector<WORKER> A, B, C;
	readData(filePath, A);
	Sort(A);
	cout << "�����Ĺ�����ϢΪ��" << endl;
	Display(A);
	Fliter(A, B, 15);
	cout << "������ڵ���15�Ĺ�����ϢΪ��" << endl;
	Display(B);
	C = Fliter(A, 2500.0);
	cout << "���ʴ��ڵ���2500.0�Ĺ�����ϢΪ��" << endl;
	Display(C);
	return 0;
}


// ����ʵ��
/*========================
����˵����
	���ļ��е����ݶ��������ҹ�����������
����˵����
	filename: �ļ�·��
	workerVector: ��������
========================*/
int readData(const string& filePath, vector<WORKER>& workerVector) {
	ifstream fin(filePath);	// ���ļ�
	if (!fin) {
		cout << "�ļ���ʧ��" << endl;
		return -1;
	}
	while (!fin.eof()) {
		WORKER worker;		// �������˽ṹ��
		// ��ȡ��������
		fin >> worker.ID >> worker.Name >> worker.WorkYears >> worker.Salary;
		workerVector.push_back(worker);	// �����ڹ�������
	}
	fin.close();				// �ر��ļ�
	return 0;
}

/*========================
����˵����
	�����������е�Ԫ�ؽ�������
����˵����
	Arr: ��������
========================*/
void Sort(vector<WORKER>& Arr) {
	bool mycmp(const WORKER & left, const WORKER & right);	// ʹ�ø�������mycmp
	sort(Arr.begin(), Arr.end(), mycmp);		// ����
}

/*========================
����˵����
	�����������е�Ԫ����ʾ����Ļ��
����˵����
	workerVector: ��������
========================*/
void Display(const vector<WORKER>& workerVector) {
	for (unsigned i = 0; i < workerVector.size(); i++) {
		cout << setw(10) << setiosflags(ios::left) << workerVector[i].ID;	// ����
		cout << setw(10) << setiosflags(ios::right) << workerVector[i].Name;// ����
		cout << setw(5) << setiosflags(ios::right) << workerVector[i].WorkYears << " ";	 // ����
		cout << setiosflags(ios::right|ios::fixed) << setprecision(1) << workerVector[i].Salary;	 // ����
		cout << resetiosflags(ios::left | ios::right | ios::fixed) << endl;
	}
}

/*========================
����˵����
	�����������й�����ڵ���X�Ĺ�������������µ�������
����˵����
	workerVectorA: ��������
	workerVectorB: �µ�����
	X: ����
========================*/
void Fliter(const vector<WORKER>& workerVectorA, vector<WORKER>& workerVectorB, int X) {
	for (unsigned i = 0; i < workerVectorA.size(); i++) {
		// �жϹ��˹����Ƿ���ڵ���X
		if (workerVectorA[i].WorkYears >= X) {
			workerVectorB.push_back(workerVectorA[i]);
		}
	}
}

/*========================
����˵����
	�����������й��ʴ��ڵ���Y�Ĺ�������������µ�������
����˵����
	workerVector: ��������
	Y: ����
����ֵ˵����
	�µ�����
========================*/
vector<WORKER> Fliter(const vector<WORKER>& workerVector, double Y) {
	vector<WORKER> workerVectorC;
	for (unsigned i = 0; i < workerVector.size(); i++) {
		// �жϹ��˹����Ƿ���ڵ���X
		if (workerVector[i].Salary >= Y) {
			workerVectorC.push_back(workerVector[i]);
		}
	}
	return workerVectorC;
}

// ��������
/*========================
����˵����
	�����������������������Name�����ֵ��������������
����˵����
	left, right: ����
========================*/
bool mycmp(const WORKER& left, const WORKER& right) {
	return (left.Name < right.Name);
}