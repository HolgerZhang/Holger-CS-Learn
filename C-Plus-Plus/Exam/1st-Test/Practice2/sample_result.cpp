#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// �ṹ������
typedef struct {
	int id;
	string name;
	int age;
	char sex;
	vector<int> interest; //�������洢�û��Ķ����Ȥ
} User;

// ��������
int read_data(const string& filename, vector<User>& vec_user);
void sort(vector<User>& vec_user);
void print(const vector<User>& vec_user);
void myfilter(const vector<User>& vec_user, vector<User>& vec_a, int X = 0);
vector<User> myfilter(const vector<User>& vec_a, int L = 20, int H = 30);

// ������
int main() {
	string filename = "d:\\data.txt";
	vector<User> vec_user, vec_a, vec_b;
	read_data(filename, vec_user);
	sort(vec_user);
	cout << "������û���Ϣ��" << endl;
	print(vec_user);
	myfilter(vec_user, vec_a, 1);
	cout << "�Ե�Ӱ����Ȥ���û���Ϣ��" << endl;
	print(vec_a);
	vec_b = myfilter(vec_a, 22);
	cout << "�Ե�Ӱ����Ȥ��������22���30��֮����û���Ϣ��" << endl;
	print(vec_b);
	return 0;
}

// ����ʵ��
/*========================
����˵����
	��ȡ�ļ��е��û����ݣ��������û���Ϣ������һ���û�������
����˵����
	filename: �ļ�·��
	vec_user: �û�����
========================*/
int read_data(const string& filename, vector<User>& vec_user) {
	ifstream fin(filename);	// ���ļ�
	if (!fin) {
		cout << "�ļ���ʧ��" << endl;
		return -1;
	}
	while (!fin.eof()) {
		User user;			// �����û��ṹ��
		string interest;		// �����û���Ȥ�ַ���
		// ��ȡ��������
		fin >> user.id >> user.name >> user.age >> user.sex;
		getline(fin, interest);	// ��ȡ�û���Ȥ�ַ���
		// �ָ��û���Ȥ�ַ���
		for (unsigned i = 0; i < interest.length(); i++) {
			if (interest[i] != ' ') {
				user.interest.push_back(interest[i] - '0');
			}
		}
		vec_user.push_back(user);	// �������û�����
	}
	fin.close();				// �ر��ļ�
}

/*========================
����˵����
	���û������е�Ԫ�ؽ�������
����˵����
	vec_user: �û�����
========================*/
void sort(vector<User>& vec_user) {
	bool mycmp(const User & left, const User & right);	// ʹ�ø�������mycmp
	sort(vec_user.begin(), vec_user.end(), mycmp);		// ����
}

/*========================
����˵����
	���û������е�Ԫ����ʾ����Ļ��
����˵����
	vec_user: �û�����
========================*/
void print(const vector<User>& vec_user) {
	for (unsigned i = 0; i < vec_user.size(); i++) {
		cout << setw(5) << setiosflags(ios::left) << vec_user[i].id;		// �û����
		cout << setw(10) << setiosflags(ios::right) << vec_user[i].name;// ����
		cout << setw(3) << setiosflags(ios::right) << vec_user[i].age;	// ����
		cout << setw(3) << setiosflags(ios::right) << vec_user[i].sex;	// �Ա�
		for (unsigned j = 0; j < vec_user[i].interest.size(); j++) {		// ��Ȥ
			switch (vec_user[i].interest[j]) {
			case 0: cout << setw(10) << setiosflags(ios::right) << "music"; break;
			case 1: cout << setw(10) << setiosflags(ios::right) << "movie"; break;
			case 2: cout << setw(10) << setiosflags(ios::right) << "reading"; break;
			case 3: cout << setw(10) << setiosflags(ios::right) << "travel"; break;
			}
		}
		cout << resetiosflags(ios::left | ios::right) << endl;	// ����
	}
}

/*========================
����˵����
	���û������ж�X����Ȥ���û�����������µ�����vec_a��
����˵����
	vec_user: �û�����
	vec_a: �µ�����
	X: ��Ȥ���
========================*/
void myfilter(const vector<User>& vec_user, vector<User>& vec_a, int X) {
	for (unsigned i = 0; i < vec_user.size(); i++) {
		for (unsigned j = 0; j < vec_user[i].interest.size(); j++) {
			// �ж��û��Ƿ��X����Ȥ
			if (vec_user[i].interest[j] == X) {
				vec_a.push_back(vec_user[i]);
				break;
			}
		}
	}
}

/*========================
����˵����
	������vec_a��������ڵ���L����С�ڵ���H���û�����������µ�����vec_b�У�
����˵����
	vec_a: �û�����
	L, H: �������յ�
����ֵ˵����
	�µ�����vec_b
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


// ��������
/*========================
����˵����
	�����������Ȱ����û���Ȥ����Ŀ�������У�
	����û�������ͬ����Ȥ��Ŀ�����������������С�
����˵����
	left, right: �û�
========================*/
bool mycmp(const User& left, const User& right) {
	if (left.interest.size() == right.interest.size()) {
		return (left.age < right.age);
	}
	return (left.interest.size() > right.interest.size());
}