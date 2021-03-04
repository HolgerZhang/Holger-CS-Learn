#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 结构体声明
typedef struct {
	int id;
	string name;
	int age;
	char sex;
	vector<int> interest; //该向量存储用户的多个兴趣
} User;

// 函数声明
int read_data(const string& filename, vector<User>& vec_user);
void sort(vector<User>& vec_user);
void print(const vector<User>& vec_user);
void myfilter(const vector<User>& vec_user, vector<User>& vec_a, int X = 0);
vector<User> myfilter(const vector<User>& vec_a, int L = 20, int H = 30);

// 主函数
int main() {
	string filename = "d:\\data.txt";
	vector<User> vec_user, vec_a, vec_b;
	read_data(filename, vec_user);
	sort(vec_user);
	cout << "排序后用户信息：" << endl;
	print(vec_user);
	myfilter(vec_user, vec_a, 1);
	cout << "对电影感兴趣的用户信息：" << endl;
	print(vec_a);
	vec_b = myfilter(vec_a, 22);
	cout << "对电影感兴趣且年龄在22岁和30岁之间的用户信息：" << endl;
	print(vec_b);
	return 0;
}

// 函数实现
/*========================
函数说明：
	读取文件中的用户数据，将所有用户信息保存在一个用户向量中
参数说明：
	filename: 文件路径
	vec_user: 用户向量
========================*/
int read_data(const string& filename, vector<User>& vec_user) {
	ifstream fin(filename);	// 打开文件
	if (!fin) {
		cout << "文件打开失败" << endl;
		return -1;
	}
	while (!fin.eof()) {
		User user;			// 创建用户结构体
		string interest;		// 储存用户兴趣字符串
		// 读取基础数据
		fin >> user.id >> user.name >> user.age >> user.sex;
		getline(fin, interest);	// 读取用户兴趣字符串
		// 分割用户兴趣字符串
		for (unsigned i = 0; i < interest.length(); i++) {
			if (interest[i] != ' ') {
				user.interest.push_back(interest[i] - '0');
			}
		}
		vec_user.push_back(user);	// 保存在用户向量
	}
	fin.close();				// 关闭文件
}

/*========================
函数说明：
	将用户向量中的元素进行排序
参数说明：
	vec_user: 用户向量
========================*/
void sort(vector<User>& vec_user) {
	bool mycmp(const User & left, const User & right);	// 使用辅助函数mycmp
	sort(vec_user.begin(), vec_user.end(), mycmp);		// 排序
}

/*========================
函数说明：
	将用户向量中的元素显示到屏幕上
参数说明：
	vec_user: 用户向量
========================*/
void print(const vector<User>& vec_user) {
	for (unsigned i = 0; i < vec_user.size(); i++) {
		cout << setw(5) << setiosflags(ios::left) << vec_user[i].id;		// 用户编号
		cout << setw(10) << setiosflags(ios::right) << vec_user[i].name;// 姓名
		cout << setw(3) << setiosflags(ios::right) << vec_user[i].age;	// 年龄
		cout << setw(3) << setiosflags(ios::right) << vec_user[i].sex;	// 性别
		for (unsigned j = 0; j < vec_user[i].interest.size(); j++) {		// 兴趣
			switch (vec_user[i].interest[j]) {
			case 0: cout << setw(10) << setiosflags(ios::right) << "music"; break;
			case 1: cout << setw(10) << setiosflags(ios::right) << "movie"; break;
			case 2: cout << setw(10) << setiosflags(ios::right) << "reading"; break;
			case 3: cout << setw(10) << setiosflags(ios::right) << "travel"; break;
			}
		}
		cout << resetiosflags(ios::left | ios::right) << endl;	// 换行
	}
}

/*========================
函数说明：
	将用户向量中对X有兴趣的用户数据输出到新的向量vec_a中
参数说明：
	vec_user: 用户向量
	vec_a: 新的向量
	X: 兴趣编号
========================*/
void myfilter(const vector<User>& vec_user, vector<User>& vec_a, int X) {
	for (unsigned i = 0; i < vec_user.size(); i++) {
		for (unsigned j = 0; j < vec_user[i].interest.size(); j++) {
			// 判断用户是否对X有兴趣
			if (vec_user[i].interest[j] == X) {
				vec_a.push_back(vec_user[i]);
				break;
			}
		}
	}
}

/*========================
函数说明：
	将向量vec_a中年龄大于等于L并且小于等于H的用户数据输出到新的向量vec_b中，
参数说明：
	vec_a: 用户向量
	L, H: 年龄起终点
返回值说明：
	新的向量vec_b
========================*/
vector<User> myfilter(const vector<User>& vec_a, int L, int H) {
	vector<User> vec_b;
	for (unsigned i = 0; i < vec_a.size(); i++) {
		if (vec_a[i].age>=L&& vec_a[i].age <= H) {
			vec_b.push_back(vec_a[i]);
		}
	}
	return vec_b;
}


// 辅助函数
/*========================
函数说明：
	辅助排序：首先按照用户兴趣的数目降序排列，
	如果用户具有相同的兴趣数目，则按照年龄升序排列。
参数说明：
	left, right: 用户
========================*/
bool mycmp(const User& left, const User& right) {
	if (left.interest.size() == right.interest.size()) {
		return (left.age < right.age);
	}
	return (left.interest.size() > right.interest.size());
}