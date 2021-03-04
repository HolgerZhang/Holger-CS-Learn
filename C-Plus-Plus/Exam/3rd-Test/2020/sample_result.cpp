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
	int m_ID;		//工号
	string m_Name;	//姓名
	int m_Sex;		//性别	0代表女性	1代表男性
	int m_Age;		//年龄

public:
	CWorker(int ID, string Name, int Sex, int Age)
	{
		if (Sex < 0 || Sex > 1)
		{
			cout << "性别初始值" << Sex << "不符合要求！" << endl;
			exit(0);
		}
		if (Age <= 0)
		{
			cout << "年龄初始值" << Age << "不符合要求！" << endl;
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
 * @brief CBenchWorker类，用于描述钳工
 *******************************************/
class CBenchWorker : public CWorker {
private:
	int m_Grade; // 钳工级别 1-5，最大为5级
public:
	/*******************************************
	 * @brief 构造函数
	 * @param ID 工号，默认值0
	 * @param Name 姓名，默认值"No Name"
	 * @param Sex 性别，默认值男性（1）
	 * @param Age 年龄。默认值18
	 * @param Grade 钳工等级，默认值1
	 ******************************************/
	CBenchWorker(int ID = 0, string Name = "No Name", int Sex = 1, int Age = 18, int Grade = 1)
		: CWorker(ID, Name, Sex, Age) {
		if (Grade < 1 || Grade > 5) {  // 判断钳工级别是否符合要求
			cout << "钳工级别初始值" << Grade << "不符合要求！" << endl;
			exit(0);
		}
		m_Grade = Grade;
	}

	/*******************************************
	 * @brief 返回级别的成员函数
	 * @return 钳工级别
	 ******************************************/
	int GetGrade() const {
		return m_Grade;
	}

	/*******************************************
	 * @brief 前++运算符，用于将钳工的级别加1
	 * @return 自增后的对象
	 ******************************************/
	CBenchWorker& operator++() {
		m_Grade++;
		if (m_Grade < 1 || m_Grade > 5) {  // 判断钳工级别是否符合要求
			cout << "钳工级别初始值" << m_Grade << "不符合要求！" << endl;
			exit(0);
		}
		return *this;
	}

	// 重载流输出运算符<<的友元函数
	friend ostream& operator<<(ostream&, const CBenchWorker&);

};

/*******************************************
 * @brief 重载流输出运算符<<的友元函数
 * @param out 输出流类对象
 * @param worker 要输出的钳工对象
 * @return 输出流类对象
 ******************************************/
ostream& operator<<(ostream& out, const CBenchWorker& worker) {
	out << (CWorker)worker;
	out << setw(5) << worker.m_Grade;
	return out;
}

/*******************************************
 * @brief 从数据文件中读取数据，逐个生成对象并存储
 * @param file 数据文件路径
 * @param myVect 由钳工对象组成的的向量
 * @return 0-读取失败，1-读取成功
 ******************************************/
int ReadData(const string& file, vector<CBenchWorker>& myVect) {
	ifstream inFile(file);
	if (!inFile) {  // 打开是否成功
		return 0;  // 读取失败
	}
	while (!inFile.eof()) {  // 读取文件
		int id, sex, age, grade;
		string name;
		inFile >> id >> name >> sex >> age >> grade;
		myVect.push_back(CBenchWorker(id, name, sex, age, grade));
	}
	inFile.close();  // 关闭文件
	return 1;  // 读取成功
}

/*******************************************
 * @brief 显示这些钳工信息。每个钳工数据占一行
 * @param myVect 钳工信息向量
 ******************************************/
void DisplayData(const vector<CBenchWorker>& myVect) {
	for (auto& worker : myVect) {
		cout << worker << endl;
	}
}

/*******************************************
 * @brief 对所有钳工依次执行前自增运算
 *         结果仍然保存在myVect中
 * @param myVect 钳工信息向量
 ******************************************/
void InecData(vector<CBenchWorker>& myVect) {
	for (auto& worker : myVect) {
		++worker;
	}
}

/**************************************************
 * @brief 删除所有年龄大于等于X岁且级别小于等于Y级的钳工
 *         结果仍然保存在myVect中，并返回删除人数
 * @param myVect 钳工信息向量
 * @param ageX 年龄上限
 * @param gradeY 等级下限
 * @return 删除人数
 *************************************************/
int DelData(vector<CBenchWorker>& myVect, int ageX, int gradeY) {
	int number = 0;  // 删除人数
	auto iter = myVect.begin();
	while (iter != myVect.end()) {  // 遍历删除
		if (iter->GetAge() >= ageX && iter->GetGrade() <= gradeY) {  // 符合条件删除
			iter = myVect.erase(iter);
			number++;
		}
		else {  // 不符合条件自增迭代器
			++iter;
		}
	}
	return number;
}

/*******************************************
 * @brief 转小写函数
 * @param word 字符串
 * @return 小写的字符串
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
 * @brief 删除所有姓名中包含（大小写不敏感）字符串X的钳工
 *         结果仍然保存在myVect 中，并返回删除人数。
 * @param myVect 钳工信息向量
 * @param strX （大小写不敏感）包含的字符串
 * @return 删除人数
 **************************************************/
int DelData(vector<CBenchWorker>& myVect, const string& strX) {
	int number = 0;  // 删除人数
	string contain = lowerCase(strX);  // 字符串X转小写
	auto iter = myVect.begin();
	while (iter != myVect.end()) {  // 遍历删除
		string name = lowerCase(iter->GetName());  // 钳工姓名转小写
		if (name.find(contain) != string::npos) {  // 包含就删除
			iter = myVect.erase(iter);
			number++;
		}
		else {  // 不包含自增迭代器
			++iter;
		}
	}
	return number;
}

/*******************************************
 * @brief 按照排序规则比较两个钳工对象
 * @param left 左操作数
 * @param right 右操作数
 * @return true - left < right
 *          false - !(left < right)
 ******************************************/
bool cmpCBenchWorkerObj(const CBenchWorker& left, const CBenchWorker& right) {
	if (left.GetSex() == right.GetSex()) {  // 性别相同
		switch (left.GetSex()) {
		case 0:  // 女性 级别降序
			return (left.GetGrade() > right.GetGrade());
		case 1: // 男性 级别增序
			return (left.GetGrade() < right.GetGrade());
		}
	}
	return (left.GetSex() < right.GetSex());  // 女士优先
}

/*************************************************************
 * @brief 对所有钳工按照性别（女士优先，女性在前、男性在后）进行排序
 *        男性钳工中按照级别进行增序排列，女性钳工中按照级别进行降序排列
 * @param myVect 要排序的钳工向量
 *************************************************************/
void SortData(vector<CBenchWorker>& myVect) {
	sort(myVect.begin(), myVect.end(), cmpCBenchWorkerObj);
}

/*******************************************
 * @brief 将钳工信息保存到指定文件中
 *         每个钳工数据占一行
 * @param file 保存文件路径
 * @param myVect 由钳工对象组成的的向量
 * @return 0-保存失败，1-保存成功
 ******************************************/
int WriteData(const string& file, const vector<CBenchWorker>& myVect) {
	ofstream outFile(file);
	if (!outFile) {  // 打开是否成功
		return 0;  // 保存失败
	}
	for (auto& worker : myVect) {  // 写入文件
		outFile << worker << endl;
	}
	outFile.close();  // 关闭文件
	return 1;  // 保存成功

}

// 主函数测试
int main() {
	vector<CBenchWorker> a;
	int c;

	if (ReadData("d:\\workers.txt", a) == 0)
		return -1;

	cout << "文件读取后一共有 " << a.size() << " 条钳工数据：" << endl;
	DisplayData(a);

	InecData(a);

	c = DelData(a, 55, 2);	//第2个参数为年龄，第3个参数为等级
	cout << endl << "第1次删除了" << c << "个钳工数据" << endl;

	c = DelData(a, "Tom");
	cout << endl << "第2次删除了" << c << "个钳工数据" << endl;

	SortData(a);

	cout << endl << "上述流程结束后一共有 " << a.size() << " 条钳工数据：" << endl;
	DisplayData(a);

	if (WriteData("d:\\res.txt", a) == 0)
		return -1;
	cout << endl << "文件保存成功" << endl << endl;
}
