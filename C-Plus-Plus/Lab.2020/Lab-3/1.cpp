/**
 * @file    1.cpp
 * @create  2020/03/17
 * @encoding GBK
 * @author  Holger
 * @description
 * 实验三 数据类型和数组
 *  用随机数初始化一个10个元素的数组，每个元素的值都是2位数，
 *  请输出该数组元素的最大值、最小值和平均值。
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int max(int arr[], int size);

int min(int arr[], int size);

int main() {
    int nums[10];    //10个元素的数组
    int sum = 0;    //10个元素的和，为计算平均数作准备
    srand((unsigned) time(NULL));
    for (int i = 0; i < 10; i++) {
        nums[i] = rand() % 90 + 10;    //产生随机数
        sum += nums[i];
    }
    cout << "最大值：" << max(nums, 10) << endl;
    cout << "最小值：" << min(nums, 10) << endl;
    cout << "平均值：" << sum / 10.0 << endl;
    return 0;
}

/*==========================
求一个整形数组中元素的最大值
参数说明：
	arr:数组首地址
	size:数组大小
返回值说明：
	整形数组元素的最大值
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
求一个整形数组中元素的最小值
参数说明：
	arr:数组首地址
	size:数组大小
返回值说明：
	整形数组元素的最小值
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
