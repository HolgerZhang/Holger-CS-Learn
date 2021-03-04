#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;


// 函数声明
int read_data(const string& filename, vector<string>& result);
void print(const vector<string>& vec_str);
void trans_str_to_int(const vector<string>& vec_str, vector<int>& vec_int);
void print(const vector<int>& vec_int);
void find_max_min_avg(const vector<int>& vec_int, int& max, int& min, double& avg);
void select_by_num(const vector<int>& vec_int, vector<int>& vec_sel, int sel_value = 9);


// 主函数入口
int main()
{
	vector<string> vec_str_A(20);
	vector<int> vec_int_A(20);
	vector<int> vec_sel;
	int max, min;
	double avg;
	string str;

	string filename = "D:\\data_new.txt";
	// 从文件中读取所有数据
	read_data(filename, vec_str_A);
	cout << "文件中的字符串为：\n";
	print(vec_str_A);
	// 将字符串转换成整数
	trans_str_to_int(vec_str_A, vec_int_A);
	cout << "\n所有字符串转成的整数为:\n";
	print(vec_int_A);
	// 找出整数中的最大值、最小值以及计算所有整数的平均值
	find_max_min_avg(vec_int_A, max, min, avg);
	cout << "\n整数向量中的最大值、最小值和平均值为:\n";
	cout << "最大值为:  " << max << "\n";
	cout << "最小值为:  " << min << "\n";
	cout << "平均值为:  " << avg << "\n";
	// 选择能被9整除的整数
	select_by_num(vec_int_A, vec_sel);
	cout << "\n选择的整数为:\n";
	print(vec_sel);

	system("pause");
	return 0;
}


// 函数实现

int read_data(const string& filename, vector<string>& result) {
	ifstream fin(filename);	// 打开文件
	if (!fin) {
		cout << "文件打开失败" << endl;
		return -1;
	}
	for (unsigned i = 0; i < 20;	 i++) {
		string str;
		fin >> str;			// 读取并加入string向量
		result[i] = str;
	}
	fin.close();				// 关闭文件
	return 0;
}

void print(const vector<string>& vec_str) {
	for (unsigned i = 0; i < vec_str.size(); i++)
		cout << vec_str[i] << endl;
}

void trans_str_to_int(const vector<string>& vec_str, vector<int>& vec_int) {
	for (unsigned i = 0; i < vec_str.size(); i++) {
		vec_int[i] = 0;		// 转换后的整数
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

