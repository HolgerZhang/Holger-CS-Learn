#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

// �ṹ������
struct salary {
	char name[20];
	int WorkYears;
	int SalaryPart1;
	int SalaryPart2;
};
struct node {
	struct salary woker;
	struct node* next;
};

// ��������
struct node* creatList();
struct node* creatNode(const struct salary& woker);
int insert(struct node* head, struct node* ptr);
int deleteNode(struct node* pre);
int deleteList(struct node* head);
struct node* readFile(const char* filePath);
void Filter(struct node* head);
int getAverageAndLength(const struct node* head, double& average, int& length);
void writeFile(const char* filePath, const struct node* head);

int main(int argc, char** argv) {
	char org[] = "d:\\org.dat";
	char res[] = "d:\\new.txt";
	struct node* list;
	cout << "��" << org << "��ȡ����..." << endl;
	list = readFile(org);		// ��ȡ����
	if (list == NULL) {			// �ж��Ƿ��ȡ�ɹ�
		cout << "���ݶ�ȡʧ��" << endl;
		return 1;
	}
	Filter(list);				// ɾ��WorkYears>=30�Ĺ���
	double average; 
	int len;
	getAverageAndLength(list, average, len); // ��ƽ�����ʺ͹�����
	cout << "һ����" << len << "�����ˣ�ƽ������Ϊ" << average << endl;
	cout << "��" << res << "д������..." << endl;
	writeFile(res, list);		// д������
	deleteList(list);			// �ͷſռ�
	return 0;
}

// ��������ͷ���������ɹ�����ͷָ�룬ʧ�ܷ���NULL
struct node* creatList() {
	struct node* ptr;
	ptr = new struct node;
	if (ptr != NULL) {	// �ж������ڴ��Ƿ�ɹ�
		ptr->next = NULL;
	}
	return ptr;
}

// ʹ�ò���woker�����ڵ㡣�ɹ����ؽڵ�ָ�룬ʧ�ܷ���NULL
struct node* creatNode(const struct salary& woker) {
	struct node* ptr;
	ptr = new struct node;
	if (ptr != NULL) {	// �ж������ڴ��Ƿ�ɹ�
		strcpy(ptr->woker.name, woker.name);
		ptr->woker.WorkYears = woker.WorkYears;
		ptr->woker.SalaryPart1 = woker.SalaryPart1;
		ptr->woker.SalaryPart2 = woker.SalaryPart2;
		ptr->next = NULL;
	}
	return ptr;
}

// �ڽڵ�head�����ptrָ��Ľڵ�
int insert(struct node* head, struct node* ptr) {
	if (head == NULL || ptr == NULL)
		return EXIT_FAILURE;
	ptr->next = head->next;
	head->next = ptr;
	return EXIT_SUCCESS;
}

// ɾ��pre�ڵ������һ���ڵ�
int deleteNode(struct node* pre) {
	if (pre == NULL)			// �ж�pre�ڵ��Ƿ���Ч
		return EXIT_FAILURE;
	if (pre->next == NULL)	// �жϽڵ��Ƿ�Ϊβ�ڵ�
		return EXIT_FAILURE;
	struct node* next = pre->next;
	pre->next = next->next;
	delete next;
	return EXIT_SUCCESS;
}

// �ͷ�������ռ�õ��ڴ�ռ�
int deleteList(node* head) {
	if (head == NULL)	// �жϽڵ��Ƿ���Ч
		return EXIT_FAILURE;
	int type;
	do {					// ɾ���ӽڵ�
		type = deleteNode(head);
	} while (type != EXIT_FAILURE);
	delete head;			// ɾ��ͷ���
	head = NULL;
	return EXIT_SUCCESS;
}

// ���ļ��е����ݶ�������������
struct node* readFile(const char* filePath) {
	ifstream fin(filePath, ios::binary);
	if (!fin) {				// �ж��ļ��Ƿ��
		return NULL;
	}
	struct node* head;
	head = creatList();
	if (head == NULL) {		// �ж��Ƿ񴴽��ɹ�
		return head;
	}
	while (fin.peek() != EOF) {		// ��ȡ����
		struct salary worker;
		fin.read(worker.name, sizeof(worker.name));
		fin.read((char*)&worker.WorkYears, sizeof(int));
		fin.read((char*)&worker.SalaryPart1, sizeof(int));
		fin.read((char*)&worker.SalaryPart2, sizeof(int));
		if (insert(head, creatNode(worker)) == EXIT_FAILURE) {		// ���������룬�ж��Ƿ�ɹ�
			fin.close();
			return NULL;
		}
	}
	fin.close();
	return head;
}

// ɾ��WorkYears>=30�Ĺ���
void Filter(struct node* head) {
	if (head == NULL) {	// �ж�ͷ����Ƿ���Ч
		return;
	}
	struct node *pre, *self = head;
	while (self->next != NULL) {		// ɾ��WorkYears>=30�Ĺ���
		pre = self;
		self = pre->next;
		if (self->woker.WorkYears >= 30) {
			deleteNode(pre);
			self = pre;
		}
	}
}

// ��������й��˵�ƽ�����ʺ�����
int getAverageAndLength(const struct node* head, double& average, int& length) {
	average = 0.0;
	length = 0;
	if (head == NULL) {	// �ж�ͷ����Ƿ���Ч
		return EXIT_FAILURE;
	}
	double sum = 0.0;
	const struct node* self = head->next;
	while (self != NULL) {	// ��������й��˵Ĺ���֮�ͺ�����
		sum += self->woker.SalaryPart1;
		sum += self->woker.SalaryPart2;
		length++;
		self = self->next;
	}
	average = sum / length;
	return EXIT_SUCCESS;
}

// ������������д���ı��ļ���
void writeFile(const char* filePath, const struct node* head) {
	ofstream fout(filePath);
	const struct node* self = head->next;
	while (self != NULL) {	// д���ı��ļ���
		fout << setw(20) << setiosflags(ios::left) << self->woker.name;
		fout << setw(8) << setiosflags(ios::left) << self->woker.WorkYears;
		fout << setw(8) << setiosflags(ios::left) << self->woker.SalaryPart1;
		fout << setiosflags(ios::left) << self->woker.SalaryPart2;
		fout << resetiosflags(ios::left) << endl;
		self = self->next;
	}
	fout.close();
}



