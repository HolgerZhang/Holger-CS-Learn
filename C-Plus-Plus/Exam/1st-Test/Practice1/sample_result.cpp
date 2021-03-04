#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;


// �ṹ��unit����
typedef struct {
	string a; //�洢A�еĵ���
	string b; //�洢B�еĵ���
	int cab; //�洢����a�͵���b�������ĵ��й�ͬ���ִ������ܺ�
} unit;

// �ṹ��unita����
typedef struct {
	string a; //A�еĵ���
	int ca; //����a�������ĵ��г��ֵĴ����ܺ�
} unita;


// ��������
int read_data(const string& fileName, vector<unit>& vunit);
void cal_counts(const vector<unit>& vunit, vector<unita>& vunita);
void sort_units(vector<unit>& vunit);
void sort_units(vector<unita>& vunita);
void print_top_units(const vector<unita>& vunita);
void cal_probs(const vector<unit>& vunit, const vector<unita>& vunita, const string& fileName);


// ������
int main() {
	string rfn = "d:\\data.txt";
	string wfn = "d:\\prob.txt";
	vector<unit> vunit;
	vector<unita> vunita;
	read_data(rfn, vunit);
	cal_counts(vunit, vunita);
	sort_units(vunit);
	sort_units(vunita);
	cout << "A�е��ʳ��ִ���ǰ20��" << endl;
	print_top_units(vunita);
	cout << "�����������ʲ��������" << wfn << endl;
	cal_probs(vunit, vunita, wfn);
	return 0;
}


// ����ʵ��
/*========================================
����˵����
	��ȡ�ļ��е��������ݣ��������Ǵ����һ��unit��������
����˵����
	fileName: ��ȡ���ļ���·��
	vunit: unit������
����ֵ˵����
	�޷���ֵ
========================================*/
int read_data(const string& fileName, vector<unit>& vunit) {
	ifstream inFile(fileName);	// ���ļ�
	if (!inFile) {
		cout << "�ļ���ʧ��" << endl;
		return -1;
	}
	while (!inFile.eof()) {
		string lineA, lineB;		// ��A, ��B�ĵ���
		int count;				// ��C�е�����
		inFile >> lineA >> lineB >> count;
		bool found = false;		// ���vunit���Ƿ��Ѿ�����a,b��ͬ�ĵ�Ԫ
		// ��������vunit��
		for (unsigned i = 0; i < vunit.size(); i++) {
			if (vunit[i].a == lineA && vunit[i].b == lineB) {
				// ���ظ���a��b����ͬ���ִ����ۼӵ�ca��
				found = true;
				vunit[i].cab += count;
				break;
			}
		}
		if (!found)
			vunit.push_back({ lineA, lineB, count });
	}
	inFile.close();				// �ر��ļ�
	return 0;
}

/*========================================
����˵����
	��unit����������A�е����������ĵ��г��ֵĴ���
	������������������һunita������
����˵����
	vunit: unit������
	vunita: unita������
����ֵ˵����
	�޷���ֵ
========================================*/
void cal_counts(const vector<unit>& vunit, vector<unita>& vunita) {
	// ����ÿһ��vunit��Ԫ
	for (unsigned i = 0; i < vunit.size(); i++) {
		bool found = false;		// ���vunita���Ƿ��Ѿ�����a��ͬ�ĵ�Ԫ
		// ��������vunita��
		for (unsigned j = 0; j < vunita.size(); j++) {
			if (vunit[i].a == vunita[j].a) {
				// ���ظ���a����ͬ���ִ����ۼӵ�ca��
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
����˵����
	����unit�������ɸߵ�������ıȽϺ���
����˵����
	vunit: unit������
����ֵ˵����
	�޷���ֵ
========================================*/
void sort_units(vector<unit>& vunit) {
	bool cmp_unit(const unit & left, const unit & right);	// ʹ�ø����ȽϺ���cmp_unit
	sort(vunit.begin(), vunit.end(), cmp_unit);
}

/*========================================
����˵����
	����unita�������ɸߵ�������ıȽϺ���
����˵����
	vunita: unita������
����ֵ˵����
	�޷���ֵ
========================================*/
void sort_units(vector<unita>& vunita) {
	bool cmp_unita(const unita & left, const unita & right);	// ʹ�ø����ȽϺ���cmp_unita
	sort(vunita.begin(), vunita.end(), cmp_unita);
}

/*========================================
����˵����
	��unita�������е�ǰ20��Ԫ���������Ļ��
����˵����
	vunita: unita������
����ֵ˵����
	�޷���ֵ
========================================*/
void print_top_units(const vector<unita>& vunita) {
	for (int i = 0; i < 20; i++) {
		cout << resetiosflags(ios::right | ios::left);	// ���ñ�׼�����״̬
		// ��ʽa����ʾ���Ϊ10��������ԡ�S�����룬�������
		cout << setw(10) << setiosflags(ios::left) << setfill('S') << vunita[i].a;
		// ��ʽca����ʽ���5��������ԡ�$�����룬���Ҷ���
		cout << setw(5) << setiosflags(ios::right) << setfill('$') << vunita[i].ca;
		cout << endl;
	}
}

/*========================================
����˵����
	������ʱ������ø��ʱ�������ļ���
����˵����
	vunit: unit������
	vunita: unita������
	fileName: д����ļ���·��
����ֵ˵����
	�޷���ֵ
========================================*/
void cal_probs(const vector<unit>& vunit, const vector<unita>& vunita, const string& fileName) {
	ofstream outFile(fileName);	// ���ļ�
	// ����vunit��Ԫ�ص�˳�����ÿһ��unitԪ��
	for (unsigned i = 0; i < vunit.size(); i++) {
		for (unsigned j = 0; j < vunita.size(); j++) {
			// �ҵ�A�е��ʶ�Ӧ��unita�ṹ��
			if (vunit[i].a == vunita[j].a) {
				double probability = (double)vunit[i].cab / vunita[j].ca;		// ������������
				outFile << vunit[i].a << "|||" << vunit[i].b << "|||" << probability << endl;
			}
		}
	}
	outFile.close();				// �ر��ļ�
}


// ��������
/*========================================
����˵����
	����unit�������ɸߵ�������ıȽϺ���
����˵����
	left��right: �Ƚϵ�����������
����ֵ˵����
	true-left>right
	false-left<=right
========================================*/
bool cmp_unit(const unit& left, const unit& right) {
	return (left.cab > right.cab);
}

/*========================================
����˵����
	����unita�������ɸߵ�������ıȽϺ���
����˵����
	left��right: �Ƚϵ�����������
����ֵ˵����
	true-left>right
	false-left<=right
========================================*/
bool cmp_unita(const unita& left, const unita& right) {
	return (left.ca > right.ca);
}
