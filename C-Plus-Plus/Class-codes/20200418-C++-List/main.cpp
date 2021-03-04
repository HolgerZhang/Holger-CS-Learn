#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

// 结构体声明
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

// 函数声明
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
	cout << "从" << org << "读取数据..." << endl;
	list = readFile(org);		// 读取数据
	if (list == NULL) {			// 判断是否读取成功
		cout << "数据读取失败" << endl;
		return 1;
	}
	Filter(list);				// 删除WorkYears>=30的工人
	double average; 
	int len;
	getAverageAndLength(list, average, len); // 求平均工资和工人数
	cout << "一共有" << len << "名工人，平均工资为" << average << endl;
	cout << "向" << res << "写入数据..." << endl;
	writeFile(res, list);		// 写入数据
	deleteList(list);			// 释放空间
	return 0;
}

// 创建包含头结点的链表。成功返回头指针，失败返回NULL
struct node* creatList() {
	struct node* ptr;
	ptr = new struct node;
	if (ptr != NULL) {	// 判断申请内存是否成功
		ptr->next = NULL;
	}
	return ptr;
}

// 使用参数woker创建节点。成功返回节点指针，失败返回NULL
struct node* creatNode(const struct salary& woker) {
	struct node* ptr;
	ptr = new struct node;
	if (ptr != NULL) {	// 判断申请内存是否成功
		strcpy(ptr->woker.name, woker.name);
		ptr->woker.WorkYears = woker.WorkYears;
		ptr->woker.SalaryPart1 = woker.SalaryPart1;
		ptr->woker.SalaryPart2 = woker.SalaryPart2;
		ptr->next = NULL;
	}
	return ptr;
}

// 在节点head后插入ptr指向的节点
int insert(struct node* head, struct node* ptr) {
	if (head == NULL || ptr == NULL)
		return EXIT_FAILURE;
	ptr->next = head->next;
	head->next = ptr;
	return EXIT_SUCCESS;
}

// 删除pre节点后续的一个节点
int deleteNode(struct node* pre) {
	if (pre == NULL)			// 判断pre节点是否有效
		return EXIT_FAILURE;
	if (pre->next == NULL)	// 判断节点是否为尾节点
		return EXIT_FAILURE;
	struct node* next = pre->next;
	pre->next = next->next;
	delete next;
	return EXIT_SUCCESS;
}

// 释放链表所占用的内存空间
int deleteList(node* head) {
	if (head == NULL)	// 判断节点是否有效
		return EXIT_FAILURE;
	int type;
	do {					// 删除子节点
		type = deleteNode(head);
	} while (type != EXIT_FAILURE);
	delete head;			// 删除头结点
	head = NULL;
	return EXIT_SUCCESS;
}

// 将文件中的数据读出，构成链表
struct node* readFile(const char* filePath) {
	ifstream fin(filePath, ios::binary);
	if (!fin) {				// 判断文件是否打开
		return NULL;
	}
	struct node* head;
	head = creatList();
	if (head == NULL) {		// 判断是否创建成功
		return head;
	}
	while (fin.peek() != EOF) {		// 读取数据
		struct salary worker;
		fin.read(worker.name, sizeof(worker.name));
		fin.read((char*)&worker.WorkYears, sizeof(int));
		fin.read((char*)&worker.SalaryPart1, sizeof(int));
		fin.read((char*)&worker.SalaryPart2, sizeof(int));
		if (insert(head, creatNode(worker)) == EXIT_FAILURE) {		// 创建并插入，判断是否成功
			fin.close();
			return NULL;
		}
	}
	fin.close();
	return head;
}

// 删除WorkYears>=30的工人
void Filter(struct node* head) {
	if (head == NULL) {	// 判断头结点是否有效
		return;
	}
	struct node *pre, *self = head;
	while (self->next != NULL) {		// 删除WorkYears>=30的工人
		pre = self;
		self = pre->next;
		if (self->woker.WorkYears >= 30) {
			deleteNode(pre);
			self = pre;
		}
	}
}

// 求出链表中工人的平均工资和人数
int getAverageAndLength(const struct node* head, double& average, int& length) {
	average = 0.0;
	length = 0;
	if (head == NULL) {	// 判断头结点是否有效
		return EXIT_FAILURE;
	}
	double sum = 0.0;
	const struct node* self = head->next;
	while (self != NULL) {	// 求出链表中工人的工资之和和人数
		sum += self->woker.SalaryPart1;
		sum += self->woker.SalaryPart2;
		length++;
		self = self->next;
	}
	average = sum / length;
	return EXIT_SUCCESS;
}

// 将链表中数据写到文本文件中
void writeFile(const char* filePath, const struct node* head) {
	ofstream fout(filePath);
	const struct node* self = head->next;
	while (self != NULL) {	// 写到文本文件中
		fout << setw(20) << setiosflags(ios::left) << self->woker.name;
		fout << setw(8) << setiosflags(ios::left) << self->woker.WorkYears;
		fout << setw(8) << setiosflags(ios::left) << self->woker.SalaryPart1;
		fout << setiosflags(ios::left) << self->woker.SalaryPart2;
		fout << resetiosflags(ios::left) << endl;
		self = self->next;
	}
	fout.close();
}



