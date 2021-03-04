/*
Լɪ��
������
	��˵������̫��ʷѧ�� Josephus�й����µĹ��£�
	��������ռ���������غ�39 ����̫����Josephus���������Ѷ㵽һ�����У�
	39����̫�˾�����Ը��Ҳ��Ҫ������ץ�������Ǿ�����һ����ɱ��ʽ��
	41�����ų�һ��ԲȦ���ɵ�1���˿�ʼ������ÿ��������3�˸��˾ͱ�����ɱ��
	Ȼ��������һ�����±�����ֱ�������˶���ɱ����Ϊֹ��
	Ȼ��Josephus ���������Ѳ�������ӡ����ȴ�һ���˿�ʼ��
	Խ��k-2���ˣ���Ϊ��һ�����Ѿ���Խ��������ɱ����k���ˡ�
	���ţ���Խ��k-1���ˣ���ɱ����k���ˡ�
	�����������ԲȦһֱ���У�ֱ������ֻʣ��һ�������£�����˾Ϳ��Լ������š�
	�����ǣ������˺ͣ�һ��ʼҪվ��ʲô�ط����ܱ��ⱻ������
	JosephusҪ���������ȼ�װ��ӣ������������Լ������ڵ�16�����31��λ�ã�
	�����ӹ����ⳡ������Ϸ��
���⣺
	�������û�����������n��k�����ڵڼ���λ�õ��˿��Ի�����
*/


#include<iostream>
using namespace std;
#include <time.h>

// �汾һ��ѭ������
int t_main() {
	int n, k;
	cout << "n=";
	cin >> n;
	cout << "k=";
	cin >> k;

	clock_t start, finish;
	start = clock();

	int* people = new int[n];	// ����
	for (unsigned i = 0; i < n; i++) {	// ��������
		*(people + i) = i + 1;
	}
	int length = n, index = 0, number = 1;
	while (length != 1) {	// ��ʼkill
		if (number % k == 0) {	// �Ƿ���k�ı���
			*(people + index) = -1;
			length--;
		}
		number++;
		while (1) {	// ����index
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
	cout << "����ʱ�䣺" << (finish - start)/(double)CLOCKS_PER_SEC << endl;

	return 0;
}

// �汾����ѭ������

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
	cout << "����ʱ�䣺" << (finish - start) / (double)CLOCKS_PER_SEC << endl;

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