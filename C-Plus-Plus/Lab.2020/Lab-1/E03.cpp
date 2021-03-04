/**
 * @file    E03.cpp
 * @create  2020/03/03
 * @encoding GBK
 * @author  Holger
 * @description ��֪2017��1��1���������գ�����2017���һ���º��գ�������������ڼ���
 */
#include <iostream>

using namespace std;

//ö�ٱ�ʾһ������
enum WEEK {
    Sun, Mon, Tues, Wed, Thur, Fri, Sat
};
//����2017��ĳ��1��ǰ�ж�����
const int DAYS_BEFORE_MONTH[] = {
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
};

//�ж������Ƿ�Ϸ�
bool judgeDate(int month, int day) {
    //�ж�month�Ƿ�Ϸ�
    if (month < 1 || month > 12)
        return false;
    //�ж�day�Ƿ�Ϸ�
    //DAYS_BEFORE_MONTH[month]-DAYS_BEFORE_MONTH[month-1]��ʾ��������
    if (day < 1 || day > DAYS_BEFORE_MONTH[month] - DAYS_BEFORE_MONTH[month - 1])
        return false;
    return true;
}

int main() {
    int month, day;
    for (;;) {
        //��ȡ���ж������Ƿ�Ϸ�
        cout << "�£�";
        cin >> month;
        cout << "�գ�";
        cin >> day;
        if (judgeDate(month, day))
            break;
        else
            cout << "�����������������룡" << endl;
    }

    //һ���еĵڼ��죨��0��ʼ��
    int totalDays = day + DAYS_BEFORE_MONTH[month - 1] - 1;
    //����������
    cout << "2017��" << month << "��" << day << "��������";
    switch (totalDays % 7) {
        case Sun:
            cout << "��" << endl;
            break;
        case Mon:
            cout << "һ" << endl;
            break;
        case Tues:
            cout << "��" << endl;
            break;
        case Wed:
            cout << "��" << endl;
            break;
        case Thur:
            cout << "��" << endl;
            break;
        case Fri:
            cout << "��" << endl;
            break;
        case Sat:
            cout << "��" << endl;
            break;
    }

    return 0;
}