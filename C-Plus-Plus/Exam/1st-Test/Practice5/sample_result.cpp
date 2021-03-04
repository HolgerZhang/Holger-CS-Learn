#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;


// 结构体定义

struct mark
{
	string xh;//学号
	string kc;//课程名称
	int    cj;//成绩
};

struct student
{
	string xh;		//学号
	int	math;		//数学成绩
	int english;		//英语成绩
	int cplusplus;	//C++成绩
};


// 函数声明
int ReadFile(const char* filename, vector<struct mark>& marks);
void ShowData(const vector<struct mark>& marks, unsigned number = 3);
int Filter(vector<struct mark>& marks);
vector<struct student> FillData(const vector<struct mark>& marks);
template <class _Ranit,  class _Pr>
void SortData(const _Ranit first, const _Ranit last, _Pr pred);	// 修改前的SortData
void SortData(vector<struct student>& stus);	// 修改后的SortData
bool cmp(const struct student& left, const struct student& right);
void ShowData(const vector<struct student>& stus, unsigned number);
void WriteFile(const char* filename, const vector<struct student>& stus);


// main函数如下
int main()
{
	vector <struct mark> marks;

	ReadFile("d:\\input.txt", marks); //读取文件的数据到marks

	cout << "数据总条数为：" << marks.size() << endl; //显示数据总数
	ShowData(marks, 5);

	int count = Filter(marks);//删除其中不合法的数据
	cout << "合计删除了" << count << "条不合法成绩" << endl;

	vector<struct student> stus = FillData(marks);
	cout << "汇总结果合计有" << stus.size() << "人" << endl;

	//SortData(stus.begin(), stus.end(), cmp);
	SortData(stus); // 修改后

	cout << "总分最低的5人信息为" << endl;
	ShowData(stus, 5);

	WriteFile("d:\\res.txt", stus);

	return 0;
}

int ReadFile(const char* filename, vector<struct mark>& marks) {
	ifstream fin(filename);	// 打开文件
	if (!fin) {	// 检测文件是否打开成功
		//cout << "读取文件失败";
		return -1;
	}
	while (!fin.eof()) {
		string xh, kc;	// 学号，课程名称
		int    cj;		// 成绩
		fin >> xh >> kc >> cj;	// 读取数据
		if (xh == string()) {	// 解决文件中出现空行的问题
			continue;
		}
		marks.push_back({ xh,kc,cj });	// 存入数据
	}
	fin.close();				// 关闭文件
	return 0;
}

void ShowData(const vector<struct mark>& marks, unsigned number) {
	unsigned end = min(marks.size(), number);
	for (unsigned i = 0; i < end; i++) {
		cout << setw(15) << setiosflags(ios::left) << marks[i].xh;	// 学号
		cout << setw(10) << setiosflags(ios::left) << marks[i].kc;	// 课程名称
		cout << setw(8) << setiosflags(ios::right) << marks[i].cj;	// 成绩
		cout << resetiosflags(ios::left | ios::right) << endl;
	}
}

int Filter(vector<struct mark>& marks) {
	int number = 0;
	// 使用迭代器删除不合法的数据
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
	vector<struct student> res;	// 保存结果
	for (unsigned i = 0; i < marks.size(); i++) {
		unsigned stuPos = 0;		// 学号为marks[i].xh的学生的下标
		bool found = false;		// 是否找到该学生
		for (stuPos = 0; stuPos < res.size(); stuPos++) {
			if (res[stuPos].xh == marks[i].xh) {
				found = true;
				break;
			}
		}
		if (!found) {		// 未找到，创建一个学生结构体
			res.push_back({ marks[i].xh,0,0,0 });	// 成绩初始化均为0
			stuPos = res.size() - 1;
		}
		// 根据科目保存成绩
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

// 修改前的SortData
template <class _Ranit, class _Pr>
void SortData(const _Ranit first, const _Ranit last, _Pr pred) {
	sort(first, last, pred);
}

// 修改后的SortData
void SortData(vector<struct student>& stus) {
	sort(stus.begin(), stus.end(), cmp);
}

bool cmp(const struct student& left, const struct student& right) {
	// 计算总成绩
	int sumLeft = left.math + left.english + left.cplusplus;
	int sumRight = right.math + right.english + right.cplusplus;
	if (sumLeft==sumRight) {		// 总分相同时，按照学号从小到大排序
		return (left.xh < right.xh);
	}
	// 总分从高到低排序
	return (sumLeft > sumRight);
}

void ShowData(const vector<struct student>& stus, unsigned number) {
	for (unsigned i = (stus.size()<=number ? 0u : stus.size()-number); i < stus.size(); i++) {
		cout << setw(15) << setiosflags(ios::left) << stus[i].xh;	// 学号
		cout << setw(5) << setiosflags(ios::right) << stus[i].math;		// math
		cout << setw(5) << setiosflags(ios::right) << stus[i].english;	// en
		cout << setw(5) << setiosflags(ios::right) << stus[i].cplusplus;	// cpp
		cout << resetiosflags(ios::left | ios::right) << endl;
	}
}

void WriteFile(const char* filename, const vector<struct student>& stus) {
	ofstream fout(filename);		// 打开文件
	for (unsigned i = 0; i < stus.size(); i++) {
		fout << setw(15) << setiosflags(ios::left) << stus[i].xh;	// 学号
		fout << setw(5) << setiosflags(ios::right) << stus[i].math;		// math
		fout << setw(5) << setiosflags(ios::right) << stus[i].english;	// en
		fout << setw(5) << setiosflags(ios::right) << stus[i].cplusplus;	// cpp
		fout << resetiosflags(ios::left | ios::right) << endl;
	}
	fout.close();					// 关闭文件
}
