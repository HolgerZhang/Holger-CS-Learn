#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// 工人信息的结构体类型声明
typedef struct {
	int ID;				//工号
	string Name;			//姓名
	int WorkYears;		//工龄
	float Salary;		//工资
} WORKER;

// 函数声明
int readData(const string& filePath, vector<WORKER>& workerVector);
void Sort(vector<WORKER>& Arr);
void Display(const vector<WORKER>& workerVector);
void Fliter(const vector<WORKER>& workerVectorA, vector<WORKER>& workerVectorB, int X = 10);
vector<WORKER> Fliter(const vector<WORKER>& workerVector, double Y = 1500.0);

// 主函数
int main() {
	string filePath = "d:\\input.txt";
	vector<WORKER> A, B, C;
	readData(filePath, A);
	Sort(A);
	cout << "排序后的工人信息为：" << endl;
	Display(A);
	Fliter(A, B, 15);
	cout << "工龄大于等于15的工人信息为：" << endl;
	Display(B);
	C = Fliter(A, 2500.0);
	cout << "工资大于等于2500.0的工人信息为：" << endl;
	Display(C);
	return 0;
}


// 函数实现
/*========================
函数说明：
	将文件中的数据读出，并且构建工人向量
参数说明：
	filename: 文件路径
	workerVector: 工人向量
========================*/
int readData(const string& filePath, vector<WORKER>& workerVector) {
	ifstream fin(filePath);	// 打开文件
	if (!fin) {
		cout << "文件打开失败" << endl;
		return -1;
	}
	while (!fin.eof()) {
		WORKER worker;		// 创建工人结构体
		// 读取基础数据
		fin >> worker.ID >> worker.Name >> worker.WorkYears >> worker.Salary;
		workerVector.push_back(worker);	// 保存在工人向量
	}
	fin.close();				// 关闭文件
	return 0;
}

/*========================
函数说明：
	将工人向量中的元素进行排序
参数说明：
	Arr: 工人向量
========================*/
void Sort(vector<WORKER>& Arr) {
	bool mycmp(const WORKER & left, const WORKER & right);	// 使用辅助函数mycmp
	sort(Arr.begin(), Arr.end(), mycmp);		// 排序
}

/*========================
函数说明：
	将工人向量中的元素显示到屏幕上
参数说明：
	workerVector: 工人向量
========================*/
void Display(const vector<WORKER>& workerVector) {
	for (unsigned i = 0; i < workerVector.size(); i++) {
		cout << setw(10) << setiosflags(ios::left) << workerVector[i].ID;	// 工号
		cout << setw(10) << setiosflags(ios::right) << workerVector[i].Name;// 姓名
		cout << setw(5) << setiosflags(ios::right) << workerVector[i].WorkYears << " ";	 // 工龄
		cout << setiosflags(ios::right|ios::fixed) << setprecision(1) << workerVector[i].Salary;	 // 工资
		cout << resetiosflags(ios::left | ios::right | ios::fixed) << endl;
	}
}

/*========================
函数说明：
	将工人向量中工龄大于等于X的工人数据输出到新的向量中
参数说明：
	workerVectorA: 工人向量
	workerVectorB: 新的向量
	X: 工龄
========================*/
void Fliter(const vector<WORKER>& workerVectorA, vector<WORKER>& workerVectorB, int X) {
	for (unsigned i = 0; i < workerVectorA.size(); i++) {
		// 判断工人工龄是否大于等于X
		if (workerVectorA[i].WorkYears >= X) {
			workerVectorB.push_back(workerVectorA[i]);
		}
	}
}

/*========================
函数说明：
	将工人向量中工资大于等于Y的工人数据输出到新的向量中
参数说明：
	workerVector: 工人向量
	Y: 工资
返回值说明：
	新的向量
========================*/
vector<WORKER> Fliter(const vector<WORKER>& workerVector, double Y) {
	vector<WORKER> workerVectorC;
	for (unsigned i = 0; i < workerVector.size(); i++) {
		// 判断工人工资是否大于等于X
		if (workerVector[i].Salary >= Y) {
			workerVectorC.push_back(workerVector[i]);
		}
	}
	return workerVectorC;
}

// 辅助函数
/*========================
函数说明：
	辅助工人向量排序：针对姓名Name按照字典序进行增序排序
参数说明：
	left, right: 工人
========================*/
bool mycmp(const WORKER& left, const WORKER& right) {
	return (left.Name < right.Name);
}