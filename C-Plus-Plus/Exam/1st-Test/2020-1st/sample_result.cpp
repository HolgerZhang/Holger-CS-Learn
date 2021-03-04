#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ����ͳ���ַ����ָ����Ľṹ��
typedef struct
{
	char ch;
	int count;
} Character;


// ��������

int readInfo(const char* fileName, vector<string>& words);		// ��ȡ�ļ��е����е��ʲ������Ǵ����������
int delInfo(vector<string>& words);								// ɾ�������г��ȴ���8��С��3�ĵ���
int delInfo(vector<string>& words, char ch);						// ɾ��������ɾ������ָ���ַ�ch��Ԫ��
void showInfo(const vector<string>& words, int num = 5);			// ��ʾwords������ǰ10������(�������10��������ȫ����ʾ)
vector<string> filterInfo(const vector<string>& words);			// ��words��ɸѡ��������Сд��ĸ�����ַ��ĵ��ʲ���������
void sortInfo(vector<string>& words);							// �Ե���������������
bool compare(const string& left, const string& right);			// �����������Ƚ���������
string lowerCase(const string& word);							// �������������ؽ�����ת��ΪСд�ĵ���
int writeInfo(const char*, const vector<string>&);				// ������д�뵽�ı��ļ�
char getTopmostChar(const vector<string>& words);				// �ҵ������г��ִ��������ַ�
bool comp(const Character& left, const Character& right);		// �����������Ƚ�����Character����


// ������
int main()
{
	vector<string> words;
	vector<string> specialWords;
	if (readInfo("d:\\info.txt", words) == -1)
	{
		cout << "��d:\\info.txt�ļ�ʧ��" << endl;
	}
	else
	{
		cout << "��ȡ��" << words.size() << "������" << endl;
	}
	cout << "ɾ���˳��ȴ���8��С��3�ĵ���" << delInfo(words) << "��" << endl;
	cout << "ɾ���˰����ַ�','�ĵ���" << delInfo(words, ',') << "��" << endl;
	cout << "ɾ�����ǰ10�������ǣ�\n";
	showInfo(words, 6);
	specialWords = filterInfo(words);
	cout << "\nɸѡ��" << specialWords.size() << "�����ʣ�ǰ10�������ǣ�" << endl;
	showInfo(specialWords);

	sortInfo(specialWords);
	cout << "\n������ǰ10�������ǣ�\n";
	showInfo(specialWords);
	writeInfo("d:\\result.txt", specialWords);
	char ch = getTopmostChar(specialWords);
	cout << "\nspecialWords�г��ִ��������ַ���" << ch << endl;
	return 0;
}


// ����ʵ��

// ��ȡ�ļ��е����е��ʣ��������Ǵ����string���͵�words������
int readInfo(const char* fileName, vector<string>& words)
{
	ifstream fin(fileName);	// ���ļ�

	if (!fin) {				// ����ļ��Ƿ�򿪳ɹ�
		return -1;
	}

	while (!fin.eof()) {		// ��ȡ����
		string word;
		fin >> word;
		words.push_back(word);
	}

	fin.close();				// �ر��ļ�
	return 0;
}


// ɾ�������г��ȴ���8��С��3�ĵ���
int delInfo(vector<string>& words)
{
	int number = 0;			// ɾ�����ݵĸ���
	vector<string>::iterator iter = words.begin();
	// ʹ�õ�����ɾ��
	while (iter != words.end()) {

		if (iter->length() > 8 || iter->length() < 3) {
			// ���ȴ���8��С��3ɾ����������ָ����һ��Ҫ�жϵ�Ԫ��
			iter = words.erase(iter);
			number++;
		}
		else {				// ��������������������
			++iter;
		}

	}
	return number;
}


// ɾ��������ɾ������ָ���ַ�ch��Ԫ��
int delInfo(vector<string>& words, char ch)
{
	int number = 0;			// ɾ�����ݵĸ���
	vector<string>::iterator iter = words.begin();
	// ʹ�õ�����ɾ��
	while (iter != words.end()) {

		if (iter->find(ch) != string::npos) {
			// iterָ�򵥴ʰ���ָ���ַ���Ԫ��chɾ��
			iter = words.erase(iter);
			number++;
		}
		else {				// ��������������������
			++iter;
		}

	}
	return number;
}


// ��ʾwords������ǰ10������(�������10��������ȫ����ʾ)
void showInfo(const vector<string>& words, int num)
{
	unsigned end = words.size() < 10 ? words.size() : 10;
	for (unsigned i = 0; i < end; i++) {		// ���ǰend������
		cout << setw(10) << setiosflags(ios::right) << words[i];
		if ((i + 1) % num == 0) {			// ÿ���num�����ʻ�һ��
			cout << endl;
		}
	}
}


// ��words��ɸѡ��������Сд��ĸ�����ַ��ĵ��ʲ���������
vector<string> filterInfo(const vector<string>& words)
{
	vector<string> resultWords;
	for (unsigned i = 0; i < words.size(); i++) {	// ����words�е���

		for (unsigned j = 0; j < words[i].length(); j++) {
			// �жϵ����Ƿ������Сд��ĸ�����ַ�
			if (!((words[i][j] >= 'a' && words[i][j] <= 'z') || (words[i][j] >= 'A' && words[i][j] <= 'Z'))) {
				resultWords.push_back(words[i]);
				break;
			}
		}

	}
	return resultWords;
}


// �Ե���������������
void sortInfo(vector<string>& words)
{
	sort(words.begin(), words.end(), compare);
}


// �����������Ƚ���������
bool compare(const string& left, const string& right)
{
	if (left.length() == right.length()) {	// �������ʱ������ASCIIֵ��С��������
		return (lowerCase(left) < lowerCase(right));
	}

	// �����յ��ʳ��ȴ�С��������
	return (left.length() < right.length());
}


// �������������ؽ�����ת��ΪСд�ĵ���
string lowerCase(const string& word)
{
	string newWord(word);	// ����ת����ĵ���
	for (unsigned i = 0; i < newWord.length(); i++) {
		// ��д��ĸת��Сд��ĸ
		if (newWord[i] >= 'A' && newWord[i] <= 'Z') {
			newWord[i] += 32;
		}
	}
	return newWord;
}


// ������д�뵽�ı��ļ��������뵥��֮���ÿո�ֿ���ÿ10�����ʻ�һ��
int writeInfo(const char* fileName, const vector<string>& words)
{
	ofstream fout(fileName);		// ���ļ�

	if (!fout) {		// ����ļ��Ƿ�򿪳ɹ�
		return -1;
	}

	for (unsigned i = 0; i < words.size(); i++) {		// д���ļ�
		fout << words[i];
		if ((i + 1) % 10 == 0) {		// ÿд��10�����ʻ�һ��
			fout << endl;
		}
		else {						// �����ÿո����
			fout << ' ';
		}
	}

	fout.close();					// �ر��ļ�
	return 0;

}


// �ҵ������г��ִ��������ַ�
char getTopmostChar(const vector<string>& words)
{
	// ͳ���ַ����ִ���
	vector<Character> characterSet;
	// ���������е�ÿһ������
	for (unsigned i = 0; i < words.size(); i++) {

		// ���������е�ÿһ���ַ�
		for (unsigned j = 0; j < words[i].length(); j++) {
			// �����ַ���Character���������Ƿ��Ѿ�����
			bool found = false;			// �Ƿ����
			for (unsigned k = 0; k < characterSet.size(); k++) {
				if (characterSet[k].ch == words[i][j]) {		// �ҵ�+1
					characterSet[k].count++;
					found = true;
					break;
				}
			}
			// δ�ҵ�����������characterSet
			if (!found) {
				Character newChar;
				newChar.ch = words[i][j];
				newChar.count = 1;		// �״γ��ּ�Ϊ1
				characterSet.push_back(newChar);
			}
		}

	}

	// ͨ�������ҵ����ִ��������ַ�
	sort(characterSet.begin(), characterSet.end(), comp);

	return characterSet.begin()->ch;
}


// �����������Ƚ�����Character����
bool comp(const Character& left, const Character& right)
{
	if (left.count == right.count) {		// ���ִ������ʱ������ASCIIֵ��С��������
		return (left.ch < right.ch);
	}

	// �����ճ��ִ����Ӵ�С����
	return (left.count > right.count);
}

