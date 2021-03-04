/**
 * @file    E02.cpp
 * @create  2020/03/07
 * @encoding GBK
 * @author  Holger
 * @description �� Sn = a + aa + ... + aa...a ��ֵ������a��һ�����֡�a��n�����ɼ������롣
 *  ���磺��  S = 2 + 22 + 222 + 2222 + 22222 + 222222����ôa = 2��n = 6��
 */
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int a, n;
    cout << "������a=";
    cin >> a;
    cout << "������n=";
    cin >> n;
    if (n < 0) {    //�ж�n�Ƿ�Ϸ�
        cout << "n����Ϊ0" << endl;
        return 0;
    }
    long sum = 0;        //�����ܺ�
    for (int i = 0; i < n; i++) {
        long each = 0;   //����an
        for (int j = 0; j <= i; j++) {  //����an
            each += a * pow(10, j);
        }
        sum += each;     //�ۼӵ�sun��
    }
    cout << "S=" << sum << endl;
    return 0;
}