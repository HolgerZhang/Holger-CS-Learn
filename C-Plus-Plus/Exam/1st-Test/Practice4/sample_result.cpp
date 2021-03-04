#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;


// ��������
int read_data(const string& filename, vector<string>& result);
void print(const vector<string>& vec_str);
void trans_str_to_int(const vector<string>& vec_str, vector<int>& vec_int);
void print(const vector<int>& vec_int);
void find_max_min_avg(const vector<int>& vec_int, int& max, int& min, double& avg);
void select_by_num(const vector<int>& vec_int, vector<int>& vec_sel, int sel_value = 9);


// ���������
int main()
{
	vector<string> vec_str_A(20);
	vector<int> vec_int_A(20);
	vector<int> vec_sel;
	int max, min;
	double avg;
	string str;

	string filename = "D:\\data_new.txt";
	// ���ļ��ж�ȡ��������
	read_data(filename, vec_str_A);
	cout << "�ļ��е��ַ���Ϊ��\n";
	print(vec_str_A);
	// ���ַ���ת��������
	trans_str_to_int(vec_str_A, vec_int_A);
	cout << "\n�����ַ���ת�ɵ�����Ϊ:\n";
	print(vec_int_A);
	// �ҳ������е����ֵ����Сֵ�Լ���������������ƽ��ֵ
	find_max_min_avg(vec_int_A, max, min, avg);
	cout << "\n���������е����ֵ����Сֵ��ƽ��ֵΪ:\n";
	cout << "���ֵΪ:  " << max << "\n";
	cout << "��СֵΪ:  " << min << "\n";
	cout << "ƽ��ֵΪ:  " << avg << "\n";
	// ѡ���ܱ�9����������
	select_by_num(vec_int_A, vec_sel);
	cout << "\nѡ�������Ϊ:\n";
	print(vec_sel);

	system("pause");
	return 0;
}


// ����ʵ��

int read_data(const string& filename, vector<string>& result) {
	ifstream fin(filename);	// ���ļ�
	if (!fin) {
		cout << "�ļ���ʧ��" << endl;
		return -1;
	}
	for (unsigned i = 0; i < 20;	 i++) {
		string str;
		fin >> str;			// ��ȡ������string����
		result[i] = str;
	}
	fin.close();				// �ر��ļ�
	return 0;
}

void print(const vector<string>& vec_str) {
	for (unsigned i = 0; i < vec_str.size(); i++)
		cout << vec_str[i] << endl;
}

void trans_str_to_int(const vector<string>& vec_str, vector<int>& vec_int) {
	for (unsigned i = 0; i < vec_str.size(); i++) {
		vec_int[i] = 0;		// ת���������
		for (unsigned j = 0; j < vec_str[i].length(); j++)
			vec_int[i] += (int)vec_str[i][j];
	}
}

void print(const vector<int>& vec_int) {
	for (unsigned i = 0; i < vec_int.size(); i++) {
		cout << setw(8) << setiosflags(ios::right) << vec_int[i];
		if ((i + 1) % 5 == 0)
			cout << endl;
	}
	if (vec_int.size()%5!=0)
		cout << endl;
}

void find_max_min_avg(const vector<int>& vec_int, int& MAX, int& MIN, double& AVG) {
	int sum = 0;
	MAX = 0;
	MIN = 0;
	for (unsigned i = 0; i < vec_int.size(); i++) {
		sum += vec_int[i];
		MAX = max(MAX, vec_int[i]);
		MIN = min(MIN, vec_int[i]);
	}
	AVG = (double)sum / vec_int.size();
}

void select_by_num(const vector<int>& vec_int, vector<int>& vec_sel, int sel_value) {
	for (unsigned i = 0; i < vec_int.size(); i++) {
		if (vec_int[i] % sel_value == 0)
			vec_sel.push_back(vec_int[i]);
	}
}

