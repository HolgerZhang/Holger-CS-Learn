/**
 * @file    4.cpp
 * @create  2020/03/18
 * @encoding GBK
 * @author  Holger
 * @description
 * ʵ���� �������ͺ�����
 *  ��֪����  int arry [10]={13,24,35,46,57,35,79,35,93}���뽫
 *  �û������һ�����ְ��մ�С�����˳����ڶ�Ӧ��λ�ú�����������顣
 *  Ȼ���������ظ���Ԫ��ȥ���������
 * ��ע��
 *      Ҳ��ʹ��<algorithm>ͷ�ļ��е�sort�������Խ�������
 *      unique��������ȥ�ء��������Լ�д������������
==============================================================*/

#include <iostream>

using namespace std;

void swap(int &left, int &right);

void show(int nums[], int length);

void sort(int nums[], int length);

int rmRepeat(int nums[], int length);

int main() {
    int arry[10] = {13, 24, 35, 46, 57, 35, 79, 35, 93};
    cout << "������һ��������";
    cin >> arry[9];
    sort(arry, 10);    //��С��������
    cout << "���ڶ�Ӧ��λ�ú������������" << endl;
    show(arry, 10);
    //ȥ���ظ���Ԫ��
    int len = rmRepeat(arry, 10);    //���ظ���Ԫ�ظ���
    cout << "����ȥ�غ�Ϊ" << endl;
    show(arry, len);
    return 0;
}

/*==========================
�����������α���
����˵����
	left��rightΪ���������α���������
����ֵ˵����
	�޷���ֵ
==========================*/
void swap(int &left, int &right) {
    int temp = left;
    left = right;
    right = temp;
}

/*==========================
�������ǰlength��Ԫ��
����˵����
	nums:�����׵�ַ
	length:�����С
����ֵ˵����
	�޷���ֵ
==========================*/
void show(int nums[], int length) {
    for (int i = 0; i < length; i++) {
        cout << nums[i] << ' ';
    }
    cout << endl;
}

/*==========================
�������С����ԭ������(ѡ������)
����˵����
	nums:�����׵�ַ
	length:�����С
����ֵ˵����
	�޷���ֵ
==========================*/
void sort(int nums[], int length) {
    for (int i = 0; i < length - 1; ++i) {
        int minpos = i;    //����iλ����С
        for (int j = i + 1; j < length; ++j) {
            //ѡ��δ�����������СԪ�ص��±�
            if (nums[j] < nums[minpos]) {
                minpos = j;
            }
        }
        if (minpos != i) {    //��С�Ĳ���i������
            swap(nums[i], nums[minpos]);
        }
    }
}

/*==========================
������������ԭ��ȥ��(�ظ�Ԫ�ط�������ĩβ)
����˵����
	nums:�����������׵�ַ
	length:�����С
����ֵ˵����
	���鲻�ظ���Ԫ�ظ���
==========================*/
int rmRepeat(int nums[], int length) {
    //��������ظ�Ԫ��
    for (int i = length - 1; i > 0; --i) {
        //��nums[i]ǰ�������֮��ͬ��Ԫ��
        for (int j = i - 1; j >= 0; --j) {
            if (nums[i] == nums[j]) {
                //������nums[i]�ظ���Ԫ�أ���nums[i]�ƶ�������β��
                for (int k = i; k < length - 1; k++) {
                    swap(nums[k], nums[k + 1]);
                }
                length--;    //���鳤��-1������ѭ��
                break;
            }
        }
    }
    return length;
}
