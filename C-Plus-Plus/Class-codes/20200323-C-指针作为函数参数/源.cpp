//指针作为函数参数
#include<iostream>
using namespace std;

void exchange1(int, int);
void exchange2(int*, int*);
void exchange3(int*, int*);
void exchange4(int*, int*);
void exchange5(int&, int&);

int main()
{
    int m = 3, n = 5;
    cout << m << " " << n << endl;
    //exchange1(m, n);
    //exchange2(&m, &n);
    //exchange3(&m, &n);
    //exchange4(&m, &n);    报错
    exchange5(m, n);
    cout << m << " " << n << endl;
    return 0;
}

//按值传递：单向传递
void exchange1(int num1, int num2)
{
    int temp = num1;
    num1 = num2;
    num2 = temp;
    cout << num1 << " " << num2 << endl;
}
//按地址传递：双向传递
void exchange2(int* pnum1, int* pnum2)
{
    int temp = *pnum1;
    *pnum1 = *pnum2;
    *pnum2 = temp;
    cout << *pnum1 << " " << *pnum2 << endl;
}
//！指针之间的赋值：单向传递（不是用了指针就一定能双相传递）
void exchange3(int* pnum1, int* pnum2)
{
    int *ptemp = pnum1;
    pnum1 = pnum2;  //这里的几条语句仅仅使得pnum1和pnum2交换了指向的变量
    pnum2 = ptemp;  //并没有真正的修改了两者指向的数据
    cout << *pnum1 << " " << *pnum2 << endl;
}
//不要使用未初始化的指针
void exchange4(int* pnum1, int* pnum2)
{
    int* ptemp;
    *ptemp = *pnum1;    //ptemp指针没有指向的变量->错误 使用了未初始化的局部变量“ptemp”
    //正确做法：int temp; int* ptemp = &temp; *ptemp = *pnum1  实际上和exchange2一致
    *pnum1 = *pnum2;
    *pnum2 = *ptemp;
    cout << *pnum1 << " " << *pnum2 << endl;
}
//引用传递：双向传递（比指针高效）
void exchange5(int& num1, int& num2)
{
    int temp = num1;
    num1 = num2;
    num2 = temp;
    cout << num1 << " " << num2 << endl;
}


//用指针处理数组
char* myStrcpy(char* des, char* src)
{
	char* p = des;
	char* q = src;
	while (*p++ = *q++);
	return des;
}
char* revert(char* src)
{
    char* p = src;
    char* q = src;
    while (*q != '\0') q++;
    q--;
    while (p < q) {
        char temp = *p;
        *p = *q;
        *q = temp;
        p++;
        q--;
    }
    return src;
}