/**
 * @file    5.cpp
 * @create  2020/03/18
 * @encoding GBK
 * @author  Holger
 * @description
 * ʵ���� �������ͺ�����
 * ���û�����n���������洢��һ�������У�Ȼ��Ը�������ֵ���������´�š�
 * ���磬ԭ����˳��Ϊ8,6,5,4,1��Ҫ���Ϊ1,4,5,6,8��n��������ֵ���û����롣
 */

#include <iostream>
#include <vector>
#include <algorithm>        //����reverse����������һ����������

using namespace std;

int main() {
    vector<int> nums;    //����
    int n;                //�����ĸ���
    cout << "Ҫ���������ĸ�����";
    cin >> n;
    cout << "������" << n << "���������ÿո�ֿ���" << endl;
    for (int i = 0; i < n; i++) {    //��ȡ��������������
        int number;
        cin >> number;
        nums.push_back(number);
    }
    //�����е�Ԫ������
    reverse(nums.begin(), nums.end());
    //�������������
    cout << "����Ϊ��" << endl;
    for (int i = 0; i < n; i++) {
        cout << nums[i] << ' ';
    }
    cout << endl;
    return 0;
}
