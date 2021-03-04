#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;


// 结构体unit声明
typedef struct {
	string a; //存储A列的单词
	string b; //存储B列的单词
	int cab; //存储单词a和单词b在所有文档中共同出现次数的总和
} unit;

// 结构体unita声明
typedef struct {
	string a; //A列的单词
	int ca; //单词a在所有文档中出现的次数总和
} unita;


// 函数声明
int read_data(const string& fileName, vector<unit>& vunit);
void cal_counts(const vector<unit>& vunit, vector<unita>& vunita);
void sort_units(vector<unit>& vunit);
void sort_units(vector<unita>& vunita);
void print_top_units(const vector<unita>& vunita);
void cal_probs(const vector<unit>& vunit, const vector<unita>& vunita, const string& fileName);


// 主函数
int main() {
	string rfn = "d:\\data.txt";
	string wfn = "d:\\prob.txt";
	vector<unit> vunit;
	vector<unita> vunita;
	read_data(rfn, vunit);
	cal_counts(vunit, vunita);
	sort_units(vunit);
	sort_units(vunita);
	cout << "A列单词出现次数前20：" << endl;
	print_top_units(vunita);
	cout << "计算条件概率并输出到：" << wfn << endl;
	cal_probs(vunit, vunita, wfn);
	return 0;
}


// 函数实现
/*========================================
函数说明：
	读取文件中的所有数据，并将它们存放在一个unit的向量中
参数说明：
	fileName: 读取的文件的路径
	vunit: unit的向量
返回值说明：
	无返回值
========================================*/
int read_data(const string& fileName, vector<unit>& vunit) {
	ifstream inFile(fileName);	// 打开文件
	if (!inFile) {
		cout << "文件打开失败" << endl;
		return -1;
	}
	while (!inFile.eof()) {
		string lineA, lineB;		// 列A, 列B的单词
		int count;				// 列C中的数字
		inFile >> lineA >> lineB >> count;
		bool found = false;		// 标记vunit中是否已经有了a,b相同的单元
		// 存入向量vunit中
		for (unsigned i = 0; i < vunit.size(); i++) {
			if (vunit[i].a == lineA && vunit[i].b == lineB) {
				// 对重复的a和b，共同出现次数累加到ca中
				found = true;
				vunit[i].cab += count;
				break;
			}
		}
		if (!found)
			vunit.push_back({ lineA, lineB, count });
	}
	inFile.close();				// 关闭文件
	return 0;
}

/*========================================
函数说明：
	由unit的向量计算A列单词在所有文档中出现的次数
	并将计算结果保存在另一unita向量中
参数说明：
	vunit: unit的向量
	vunita: unita的向量
返回值说明：
	无返回值
========================================*/
void cal_counts(const vector<unit>& vunit, vector<unita>& vunita) {
	// 遍历每一个vunit单元
	for (unsigned i = 0; i < vunit.size(); i++) {
		bool found = false;		// 标记vunita中是否已经有了a相同的单元
		// 存入向量vunita中
		for (unsigned j = 0; j < vunita.size(); j++) {
			if (vunit[i].a == vunita[j].a) {
				// 对重复的a，共同出现次数累加到ca中
				found = true;
				vunita[j].ca += vunit[i].cab;
				break;
			}
		}
		if (!found)
			vunita.push_back({ vunit[i].a, vunit[i].cab });
	}
}

/*========================================
函数说明：
	帮助unit的向量由高到低排序的比较函数
参数说明：
	vunit: unit的向量
返回值说明：
	无返回值
========================================*/
void sort_units(vector<unit>& vunit) {
	bool cmp_unit(const unit & left, const unit & right);	// 使用辅助比较函数cmp_unit
	sort(vunit.begin(), vunit.end(), cmp_unit);
}

/*========================================
函数说明：
	帮助unita的向量由高到低排序的比较函数
参数说明：
	vunita: unita的向量
返回值说明：
	无返回值
========================================*/
void sort_units(vector<unita>& vunita) {
	bool cmp_unita(const unita & left, const unita & right);	// 使用辅助比较函数cmp_unita
	sort(vunita.begin(), vunita.end(), cmp_unita);
}

/*========================================
函数说明：
	将unita的向量中的前20个元素输出到屏幕上
参数说明：
	vunita: unita的向量
返回值说明：
	无返回值
========================================*/
void print_top_units(const vector<unita>& vunita) {
	for (int i = 0; i < 20; i++) {
		cout << resetiosflags(ios::right | ios::left);	// 重置标准输出流状态
		// 显式a，显示宽度为10，不足的以“S”补齐，向左对齐
		cout << setw(10) << setiosflags(ios::left) << setfill('S') << vunita[i].a;
		// 显式ca，显式宽度5，不足的以“$”补齐，向右对齐
		cout << setw(5) << setiosflags(ios::right) << setfill('$') << vunita[i].ca;
		cout << endl;
	}
}

/*========================================
函数说明：
	计算概率表，并将该概率表输出到文件中
参数说明：
	vunit: unit的向量
	vunita: unita的向量
	fileName: 写入的文件的路径
返回值说明：
	无返回值
========================================*/
void cal_probs(const vector<unit>& vunit, const vector<unita>& vunita, const string& fileName) {
	ofstream outFile(fileName);	// 打开文件
	// 按照vunit中元素的顺序遍历每一个unit元素
	for (unsigned i = 0; i < vunit.size(); i++) {
		for (unsigned j = 0; j < vunita.size(); j++) {
			// 找到A列单词对应的unita结构体
			if (vunit[i].a == vunita[j].a) {
				double probability = (double)vunit[i].cab / vunita[j].ca;		// 计算条件概率
				outFile << vunit[i].a << "|||" << vunit[i].b << "|||" << probability << endl;
			}
		}
	}
	outFile.close();				// 关闭文件
}


// 辅助函数
/*========================================
函数说明：
	帮助unit的向量由高到低排序的比较函数
参数说明：
	left和right: 比较的两个操作数
返回值说明：
	true-left>right
	false-left<=right
========================================*/
bool cmp_unit(const unit& left, const unit& right) {
	return (left.cab > right.cab);
}

/*========================================
函数说明：
	帮助unita的向量由高到低排序的比较函数
参数说明：
	left和right: 比较的两个操作数
返回值说明：
	true-left>right
	false-left<=right
========================================*/
bool cmp_unita(const unita& left, const unita& right) {
	return (left.ca > right.ca);
}
