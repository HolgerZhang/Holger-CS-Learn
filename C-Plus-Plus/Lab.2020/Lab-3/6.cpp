/**
 * @file    6.cpp
 * @create  2020/03/18
 * @encoding GBK
 * @author  Holger
 * @description
 * ʵ���� �������ͺ�����
 * ��д�����12���µ�Ӣ�ĵ��ʸ����ֵ�����д�С�����������ʹ��string����ʵ�֡�
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    vector<string> months = {    //12���µ�Ӣ�ĵ���
            "January", "February", "March", "April", "May", "June", "July",
            "August", "September", "October", "November", "December"
    };
    //��С��������
    sort(months.begin(), months.end());
    //�����������ÿ��ռ10�У�ÿ��6��
    for (int i = 0; i < months.size(); i++) {
        cout << setiosflags(ios_base::left);
        cout << setw(10) << months[i];
        if ((i + 1) % 6 == 0) {
            cout << endl;
        }
    }
    return 0;
}