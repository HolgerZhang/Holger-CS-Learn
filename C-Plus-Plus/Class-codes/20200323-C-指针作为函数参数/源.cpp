//ָ����Ϊ��������
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
    //exchange4(&m, &n);    ����
    exchange5(m, n);
    cout << m << " " << n << endl;
    return 0;
}

//��ֵ���ݣ����򴫵�
void exchange1(int num1, int num2)
{
    int temp = num1;
    num1 = num2;
    num2 = temp;
    cout << num1 << " " << num2 << endl;
}
//����ַ���ݣ�˫�򴫵�
void exchange2(int* pnum1, int* pnum2)
{
    int temp = *pnum1;
    *pnum1 = *pnum2;
    *pnum2 = temp;
    cout << *pnum1 << " " << *pnum2 << endl;
}
//��ָ��֮��ĸ�ֵ�����򴫵ݣ���������ָ���һ����˫�ഫ�ݣ�
void exchange3(int* pnum1, int* pnum2)
{
    int *ptemp = pnum1;
    pnum1 = pnum2;  //����ļ���������ʹ��pnum1��pnum2������ָ��ı���
    pnum2 = ptemp;  //��û���������޸�������ָ�������
    cout << *pnum1 << " " << *pnum2 << endl;
}
//��Ҫʹ��δ��ʼ����ָ��
void exchange4(int* pnum1, int* pnum2)
{
    int* ptemp;
    *ptemp = *pnum1;    //ptempָ��û��ָ��ı���->���� ʹ����δ��ʼ���ľֲ�������ptemp��
    //��ȷ������int temp; int* ptemp = &temp; *ptemp = *pnum1  ʵ���Ϻ�exchange2һ��
    *pnum1 = *pnum2;
    *pnum2 = *ptemp;
    cout << *pnum1 << " " << *pnum2 << endl;
}
//���ô��ݣ�˫�򴫵ݣ���ָ���Ч��
void exchange5(int& num1, int& num2)
{
    int temp = num1;
    num1 = num2;
    num2 = temp;
    cout << num1 << " " << num2 << endl;
}


//��ָ�봦������
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