/**
 * @file    E01.cpp
 * @create  2020/03/03
 * @encoding GBK
 * @author  Holger
 * @description
 *  ��д��������û������3��������ƽ��ֵ���͡����ֵ����Сֵ�����������Ļ�ϡ�
 *  �����ʽҪ��ƽ��ֵռ 8�У�����4λС��������룻���ֵ����Сֵռ 6�У��Ҷ��롣
 */
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int numbers[3];    //��������
    int sum = 0;       //���������ĺ�
    //�Ӽ��̶�ȡ���ݲ����
    cout << "�������������������ÿո�ֿ���";
    for (int i = 0; i < 3; ++i) {
        cin >> numbers[i];
        sum += numbers[i];
    }

    //ƽ��ֵ
    double average = (double) sum / 3;
    //���ֵ
    int bigger = (numbers[0] > numbers[1]) ? numbers[0] : numbers[1];
    int max = (bigger > numbers[2]) ? bigger : numbers[2];
    //��Сֵ
    int smaller = (numbers[0] < numbers[1]) ? numbers[0] : numbers[1];
    int min = (smaller < numbers[2]) ? smaller : numbers[2];

    //�������
    //����롢�����ʽ������ʵ������С�������λ
    cout << setiosflags(ios_base::left | ios_base::fixed)
         << setprecision(4);
    cout << "ƽ��ֵ��" << setw(8) << average << endl;
    //���״̬�����Ͷ����ʽ����Ϊ�Ҷ���
    cout << setiosflags(ios_base::left | ios_base::fixed)
         << setiosflags(ios_base::right);
    cout << "�ͣ�" << setw(6) << sum << endl;
    cout << "���ֵ��" << setw(6) << max << endl;
    cout << "��Сֵ��" << setw(6) << min << endl;

    return 0;
}
