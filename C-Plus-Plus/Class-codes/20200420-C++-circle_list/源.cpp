/*
约瑟夫环
背景：
	据说著名犹太历史学家 Josephus有过以下的故事：
	在罗马人占领乔塔帕特后，39 个犹太人与Josephus及他的朋友躲到一个洞中，
	39个犹太人决定宁愿死也不要被敌人抓到，于是决定了一个自杀方式，
	41个人排成一个圆圈，由第1个人开始报数，每报数到第3人该人就必须自杀，
	然后再由下一个重新报数，直到所有人都自杀身亡为止。
	然而Josephus 和他的朋友并不想遵从。首先从一个人开始，
	越过k-2个人（因为第一个人已经被越过），并杀掉第k个人。
	接着，再越过k-1个人，并杀掉第k个人。
	这个过程沿着圆圈一直进行，直到最终只剩下一个人留下，这个人就可以继续活着。
	问题是，给定了和，一开始要站在什么地方才能避免被处决？
	Josephus要他的朋友先假装遵从，他将朋友与自己安排在第16个与第31个位置，
	于是逃过了这场死亡游戏。
问题：
	下面由用户输入总人数n和k，问在第几个位置的人可以活下来
*/


#include<iostream>
using namespace std;
#include <time.h>

// 版本一：循环数组
int t_main() {
	int n, k;
	cout << "n=";
	cin >> n;
	cout << "k=";
	cin >> k;

	clock_t start, finish;
	start = clock();

	int* people = new int[n];	// 数组
	for (unsigned i = 0; i < n; i++) {	// 置满数组
		*(people + i) = i + 1;
	}
	int length = n, index = 0, number = 1;
	while (length != 1) {	// 开始kill
		if (number % k == 0) {	// 是否是k的倍数
			*(people + index) = -1;
			length--;
		}
		number++;
		while (1) {	// 递增index
			index++;
			if (index >= n) {
				index = 0;
			}
			if (*(people + index) != -1) {
				break;
			}
		}
	}
	cout << *(people + index) << endl;
	delete[] people;

	finish = clock();
	cout << "运行时间：" << (finish - start)/(double)CLOCKS_PER_SEC << endl;

	return 0;
}

// 版本二：循环链表

struct node {
	int key;
	struct node* next;
};

struct node* creat(int n);
int find_and_free(struct node* head, int k);

int main() {
	int n, k;
	cout << "n=";
	cin >> n;
	cout << "k=";
	cin >> k;
	
	clock_t start, finish;
	start = clock();

	int result;
	result = find_and_free(creat(n), k);
	cout << result << endl;

	finish = clock();
	cout << "运行时间：" << (finish - start) / (double)CLOCKS_PER_SEC << endl;

	return 0;
}

struct node* creat(int n) {
	struct node* head, * p1, * p2;
	head = new struct node;
	head->key = 1;
	head->next = head;
	p1 = head;
	for (int i = 1; i < n; i++) {
		p2 = new struct node;
		p2->key = i + 1;
		p2->next = head;
		p1->next = p2;
		p1 = p2;
	}
	return head;
}

int find_and_free(struct node* head, int k) {
	struct node* p1, * p2;
	p1 = &struct node({ -1,head });
	p2 = head;
	int number = 1;
	while (p1 != p2) {
		if (number % k == 0) {
			// kill
			p1->next = p2->next;
			delete p2;
			p2 = p1->next;
		}
		else
		{
			p1 = p2;
			p2 = p2->next;
		}
		number++;
	}
	int result = p1->key;
	delete p1;
	return result;
}