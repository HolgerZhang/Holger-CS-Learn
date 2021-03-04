#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// 辅助统计字符出现个数的结构体
typedef struct
{
	char ch;
	int count;
} Character;


// 函数声明

int readInfo(const char* fileName, vector<string>& words);		// 读取文件中的所有单词并将它们存放在向量中
int delInfo(vector<string>& words);								// 删除向量中长度大于8或小于3的单词
int delInfo(vector<string>& words, char ch);						// 删除向量中删除包含指定字符ch的元素
void showInfo(const vector<string>& words, int num = 5);			// 显示words向量的前10个单词(如果不足10个单词则全部显示)
vector<string> filterInfo(const vector<string>& words);			// 从words中筛选出包含大小写字母以外字符的单词并构成向量
void sortInfo(vector<string>& words);							// 对单词向量进行排序
bool compare(const string& left, const string& right);			// 辅助函数：比较两个单词
string lowerCase(const string& word);							// 辅助函数：返回将单词转化为小写的单词
int writeInfo(const char*, const vector<string>&);				// 将向量写入到文本文件
char getTopmostChar(const vector<string>& words);				// 找到向量中出现次数最多的字符
bool comp(const Character& left, const Character& right);		// 辅助函数：比较两个Character对象


// 主函数
int main()
{
	vector<string> words;
	vector<string> specialWords;
	if (readInfo("d:\\info.txt", words) == -1)
	{
		cout << "打开d:\\info.txt文件失败" << endl;
	}
	else
	{
		cout << "读取到" << words.size() << "个单词" << endl;
	}
	cout << "删除了长度大于8和小于3的单词" << delInfo(words) << "个" << endl;
	cout << "删除了包含字符','的单词" << delInfo(words, ',') << "个" << endl;
	cout << "删除后的前10个单词是：\n";
	showInfo(words, 6);
	specialWords = filterInfo(words);
	cout << "\n筛选出" << specialWords.size() << "个单词，前10个单词是：" << endl;
	showInfo(specialWords);

	sortInfo(specialWords);
	cout << "\n排序后的前10个单词是：\n";
	showInfo(specialWords);
	writeInfo("d:\\result.txt", specialWords);
	char ch = getTopmostChar(specialWords);
	cout << "\nspecialWords中出现次数最多的字符是" << ch << endl;
	return 0;
}


// 函数实现

// 读取文件中的所有单词，并将它们存放在string类型的words向量中
int readInfo(const char* fileName, vector<string>& words)
{
	ifstream fin(fileName);	// 打开文件

	if (!fin) {				// 检测文件是否打开成功
		return -1;
	}

	while (!fin.eof()) {		// 读取数据
		string word;
		fin >> word;
		words.push_back(word);
	}

	fin.close();				// 关闭文件
	return 0;
}


// 删除向量中长度大于8或小于3的单词
int delInfo(vector<string>& words)
{
	int number = 0;			// 删除数据的个数
	vector<string>::iterator iter = words.begin();
	// 使用迭代器删除
	while (iter != words.end()) {

		if (iter->length() > 8 || iter->length() < 3) {
			// 长度大于8或小于3删除，迭代器指向下一个要判断的元素
			iter = words.erase(iter);
			number++;
		}
		else {				// 不符合条件递增迭代器
			++iter;
		}

	}
	return number;
}


// 删除向量中删除包含指定字符ch的元素
int delInfo(vector<string>& words, char ch)
{
	int number = 0;			// 删除数据的个数
	vector<string>::iterator iter = words.begin();
	// 使用迭代器删除
	while (iter != words.end()) {

		if (iter->find(ch) != string::npos) {
			// iter指向单词包含指定字符的元素ch删除
			iter = words.erase(iter);
			number++;
		}
		else {				// 不符合条件递增迭代器
			++iter;
		}

	}
	return number;
}


// 显示words向量的前10个单词(如果不足10个单词则全部显示)
void showInfo(const vector<string>& words, int num)
{
	unsigned end = words.size() < 10 ? words.size() : 10;
	for (unsigned i = 0; i < end; i++) {		// 输出前end个单词
		cout << setw(10) << setiosflags(ios::right) << words[i];
		if ((i + 1) % num == 0) {			// 每输出num个单词换一行
			cout << endl;
		}
	}
}


// 从words中筛选出包含大小写字母以外字符的单词并构成向量
vector<string> filterInfo(const vector<string>& words)
{
	vector<string> resultWords;
	for (unsigned i = 0; i < words.size(); i++) {	// 遍历words中单词

		for (unsigned j = 0; j < words[i].length(); j++) {
			// 判断单词是否包含大小写字母以外字符
			if (!((words[i][j] >= 'a' && words[i][j] <= 'z') || (words[i][j] >= 'A' && words[i][j] <= 'Z'))) {
				resultWords.push_back(words[i]);
				break;
			}
		}

	}
	return resultWords;
}


// 对单词向量进行排序
void sortInfo(vector<string>& words)
{
	sort(words.begin(), words.end(), compare);
}


// 辅助函数：比较两个单词
bool compare(const string& left, const string& right)
{
	if (left.length() == right.length()) {	// 长度相等时，按照ASCII值从小到大排序
		return (lowerCase(left) < lowerCase(right));
	}

	// 否则按照单词长度从小到大排序
	return (left.length() < right.length());
}


// 辅助函数：返回将单词转化为小写的单词
string lowerCase(const string& word)
{
	string newWord(word);	// 保存转换后的单词
	for (unsigned i = 0; i < newWord.length(); i++) {
		// 大写字母转换小写字母
		if (newWord[i] >= 'A' && newWord[i] <= 'Z') {
			newWord[i] += 32;
		}
	}
	return newWord;
}


// 将向量写入到文本文件，单词与单词之间用空格分开，每10个单词换一行
int writeInfo(const char* fileName, const vector<string>& words)
{
	ofstream fout(fileName);		// 打开文件

	if (!fout) {		// 检测文件是否打开成功
		return -1;
	}

	for (unsigned i = 0; i < words.size(); i++) {		// 写入文件
		fout << words[i];
		if ((i + 1) % 10 == 0) {		// 每写入10个单词换一行
			fout << endl;
		}
		else {						// 否则用空格隔开
			fout << ' ';
		}
	}

	fout.close();					// 关闭文件
	return 0;

}


// 找到向量中出现次数最多的字符
char getTopmostChar(const vector<string>& words)
{
	// 统计字符出现次数
	vector<Character> characterSet;
	// 遍历向量中的每一个单词
	for (unsigned i = 0; i < words.size(); i++) {

		// 遍历单词中的每一个字符
		for (unsigned j = 0; j < words[i].length(); j++) {
			// 查找字符的Character计数对象是否已经存在
			bool found = false;			// 是否存在
			for (unsigned k = 0; k < characterSet.size(); k++) {
				if (characterSet[k].ch == words[i][j]) {		// 找到+1
					characterSet[k].count++;
					found = true;
					break;
				}
			}
			// 未找到，加入向量characterSet
			if (!found) {
				Character newChar;
				newChar.ch = words[i][j];
				newChar.count = 1;		// 首次出现记为1
				characterSet.push_back(newChar);
			}
		}

	}

	// 通过排序找到出现次数最多的字符
	sort(characterSet.begin(), characterSet.end(), comp);

	return characterSet.begin()->ch;
}


// 辅助函数：比较两个Character对象
bool comp(const Character& left, const Character& right)
{
	if (left.count == right.count) {		// 出现次数相等时，按照ASCII值从小到大排序
		return (left.ch < right.ch);
	}

	// 否则按照出现次数从大到小排序
	return (left.count > right.count);
}

