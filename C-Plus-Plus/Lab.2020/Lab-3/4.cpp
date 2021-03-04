/**
 * @file    4.cpp
 * @create  2020/03/18
 * @encoding GBK
 * @author  Holger
 * @description
 * 实验三 数据类型和数组
 *  已知数组  int arry [10]={13,24,35,46,57,35,79,35,93}，请将
 *  用户输入的一个数字按照从小到大的顺序插在对应的位置后输出整个数组。
 *  然后将数组中重复的元素去除后输出。
 * 备注：
 *      也可使用<algorithm>头文件中的sort函数可以进行排序；
 *      unique函数可以去重。本题中自己写这两个方法。
==============================================================*/

#include <iostream>

using namespace std;

void swap(int &left, int &right);

void show(int nums[], int length);

void sort(int nums[], int length);

int rmRepeat(int nums[], int length);

int main() {
    int arry[10] = {13, 24, 35, 46, 57, 35, 79, 35, 93};
    cout << "请输入一个整数：";
    cin >> arry[9];
    sort(arry, 10);    //从小到大排序
    cout << "插在对应的位置后的整个数组是" << endl;
    show(arry, 10);
    //去除重复的元素
    int len = rmRepeat(arry, 10);    //不重复的元素个数
    cout << "数组去重后为" << endl;
    show(arry, len);
    return 0;
}

/*==========================
交换两个整形变量
参数说明：
	left和right为待交换整形变量的引用
返回值说明：
	无返回值
==========================*/
void swap(int &left, int &right) {
    int temp = left;
    left = right;
    right = temp;
}

/*==========================
输出数组前length个元素
参数说明：
	nums:数组首地址
	length:数组大小
返回值说明：
	无返回值
==========================*/
void show(int nums[], int length) {
    for (int i = 0; i < length; i++) {
        cout << nums[i] << ' ';
    }
    cout << endl;
}

/*==========================
对数组从小到大原地排序(选择排序)
参数说明：
	nums:数组首地址
	length:数组大小
返回值说明：
	无返回值
==========================*/
void sort(int nums[], int length) {
    for (int i = 0; i < length - 1; ++i) {
        int minpos = i;    //假设i位置最小
        for (int j = i + 1; j < length; ++j) {
            //选出未排序区域的最小元素的下标
            if (nums[j] < nums[minpos]) {
                minpos = j;
            }
        }
        if (minpos != i) {    //最小的不是i，交换
            swap(nums[i], nums[minpos]);
        }
    }
}

/*==========================
对已排序数组原地去重(重复元素放在数组末尾)
参数说明：
	nums:已排序数组首地址
	length:数组大小
返回值说明：
	数组不重复的元素个数
==========================*/
int rmRepeat(int nums[], int length) {
    //倒序查找重复元素
    for (int i = length - 1; i > 0; --i) {
        //在nums[i]前面查找与之相同的元素
        for (int j = i - 1; j >= 0; --j) {
            if (nums[i] == nums[j]) {
                //发现与nums[i]重复的元素，将nums[i]移动到数组尾部
                for (int k = i; k < length - 1; k++) {
                    swap(nums[k], nums[k + 1]);
                }
                length--;    //数组长度-1，跳出循环
                break;
            }
        }
    }
    return length;
}
