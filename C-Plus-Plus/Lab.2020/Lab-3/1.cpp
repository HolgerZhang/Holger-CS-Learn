/**
 * @file    1.cpp
 * @create  2020/03/17
 * @encoding GBK
 * @author  Holger
 * @description
 * ʵ���� �������ͺ�����
 *  ���������ʼ��һ��10��Ԫ�ص����飬ÿ��Ԫ�ص�ֵ����2λ����
 *  �����������Ԫ�ص����ֵ����Сֵ��ƽ��ֵ��
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int max(int arr[], int size);

int min(int arr[], int size);

int main() {
    int nums[10];    //10��Ԫ�ص�����
    int sum = 0;    //10��Ԫ�صĺͣ�Ϊ����ƽ������׼��
    srand((unsigned) time(NULL));
    for (int i = 0; i < 10; i++) {
        nums[i] = rand() % 90 + 10;    //���������
        sum += nums[i];
    }
    cout << "���ֵ��" << max(nums, 10) << endl;
    cout << "��Сֵ��" << min(nums, 10) << endl;
    cout << "ƽ��ֵ��" << sum / 10.0 << endl;
    return 0;
}

/*==========================
��һ������������Ԫ�ص����ֵ
����˵����
	arr:�����׵�ַ
	size:�����С
����ֵ˵����
	��������Ԫ�ص����ֵ
==========================*/
int max(int arr[], int size) {
    int MaxNumber = arr[0];
    for (int i = 1; i < size; i++) {
        if (MaxNumber < arr[i]) {
            MaxNumber = arr[i];
        }
    }
    return MaxNumber;
}

/*==========================
��һ������������Ԫ�ص���Сֵ
����˵����
	arr:�����׵�ַ
	size:�����С
����ֵ˵����
	��������Ԫ�ص���Сֵ
==========================*/
int min(int arr[], int size) {
    int MinNumber = arr[0];
    for (int i = 1; i < size; i++) {
        if (MinNumber > arr[i]) {
            MinNumber = arr[i];
        }
    }
    return MinNumber;
}
