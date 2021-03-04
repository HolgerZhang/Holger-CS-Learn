#include <cstdio>
#include <iostream>
#include <iomanip>
using namespace std;


struct student
{
	int		num;
	float	score;
	struct	student* next;
};


void  print(struct  student* head);
struct  student* creat(void);
void clear_list(struct student* head);

int main(int argc, char* argv[])
{
	/*
	struct student  stu_a, stu_b, stu_c, * head, * p;

	stu_a.num = 10101;
	stu_a.score = 89.5;
	stu_b.num = 10103;
	stu_b.score = 90;
	stu_c.num = 10107;
	stu_c.score = 85;
	head = &stu_a;
	stu_a.next = &stu_b;
	stu_b.next = &stu_c;
	stu_c.next = NULL;
	p = head;
	print(p);
	*/
	struct student* ptr;

	ptr = creat();	//动态生成链表
	print(ptr);		//输出各结点的数据
	clear_list(ptr);
	return 0;
}


void  print(struct  student* head)
{
	struct  student* p;
	if (head == NULL)
		cout << "...NULL" << endl;
	else
	{
		p = head;
		while (p != NULL)
		{
			cout << setw(5) << setiosflags(ios::left)<< p->num;
			cout << setw(5) << setiosflags(ios::left | ios::fixed) << setprecision(1) << p->score << endl;
			p = p->next;
		};
	}
	return;
}


struct  student* creat(void)
{
	struct student* head;           //作为头指针
	struct student* p1, * p2;       //生成链表过程中使用
	int     num;		       //临时存放学号
	float  score;                          //临时存放成绩
	int     n;			       //结点计数

	n = 0;
	head = p1 = p2 = NULL;	       //初始化时，都指向“空”

	cout << "Please input " << n + 1 << " INFO:" << endl;
	while (1)
	{
		cout << "No.= ";
		cin >> num;
		if (num == 0)      //学号为0时，结束循环
			break;
		cout << "score= ";
		cin >> score;
		p1 = new struct student;
		n++;
		p1->num = num;
		p1->score = score;

		//为形成链表，调整相应的指针
		if (head == NULL)
		{
			head = p1;
		}
		else
		{
			p2->next = p1;
		}
		p2 = p1;
	}    //while循环结束

	if (p2 != NULL)
		p2->next = NULL;

	return (head);

}  //函数结束


// 释放链表所占用的内存空间
void clear_list(struct student* head) {
	if (head == NULL)	// 判断节点是否有效
		return;

	struct student* p1, * p2;
	p1 = head;
	while (p1 != NULL) {
		p2 = p1->next;
		delete p1;
		p1 = p2;
	}
}