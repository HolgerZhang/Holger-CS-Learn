/**
 * @file    5.cpp
 * @create  2020/03/18
 * @encoding GBK
 * @author  Holger
 * @description
 * 实验三 数据类型和数组
 * 让用户输入n个整数，存储到一个向量中，然后对该向量的值按逆序重新存放。
 * 例如，原来的顺序为8,6,5,4,1。要求改为1,4,5,6,8。n和整数的值请用户输入。
 */

#include <iostream>
#include <vector>
#include <algorithm>        //其中reverse函数用来将一个容器逆序

using namespace std;

int main() {
    vector<int> nums;    //向量
    int n;                //整数的个数
    cout << "要输入整数的个数：";
    cin >> n;
    cout << "请输入" << n << "个整数，用空格分开。" << endl;
    for (int i = 0; i < n; i++) {    //读取整数并存入向量
        int number;
        cin >> number;
        nums.push_back(number);
    }
    //向量中的元素逆序
    reverse(nums.begin(), nums.end());
    //输出逆序后的向量
    cout << "向量为：" << endl;
    for (int i = 0; i < n; i++) {
        cout << nums[i] << ' ';
    }
    cout << endl;
    return 0;
}
