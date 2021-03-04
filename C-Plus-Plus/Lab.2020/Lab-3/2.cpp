/**
 * @file    2.cpp
 * @create  2020/03/17
 * @encoding GBK
 * @author  Holger
 * @description
 * ʵ���� �������ͺ�����
 *  �Ӽ�������һ���������ո�Ľ���Ӣ����ĸ��ɵ��ַ��������Ȳ�����200
 *  ���ַ���ͳ��26��Ӣ����ĸ��ʹ��Ƶ�ʣ����ֵĴ������������ִ�Сд��
 *  ���ʹ��Ƶ�ʴӴ�С��˳�������ĸ��Сд��ĸ������ʹ��Ƶ�ʣ�
 *  û�г��ֵ���ĸ�������
 * ��ע��ʹ��mapҲ��ͳ�Ƴ���Ƶ��
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(const vector<int> &left, const vector<int> &right);

int main() {
    char str[201];    //Ӣ����ĸ��ɵ��ַ���
    cout << "������һ���������ո�Ľ���Ӣ����ĸ��ɵ��ַ��������Ȳ�����200��" << endl;
    cin >> str;
    vector<vector<int>> alphabet;    //Сд��ĸ��
    //alphabet�±������ĸ��˳��Ԫ��Ϊvector<int>
    //vector<int>�ĵ�һ��Ԫ��Ϊ��ĸ��ASCIIֵ���ڶ���Ϊ����Ƶ��
    for (char ch = 'a'; ch <= 'z'; ch++) {    //��ʼ����ĸ��
        vector<int> alpha = {ch, 0};
        alphabet.push_back(alpha);
    }
    int i = 0;
    while (str[i]) {    //ͳ����ĸ����Ƶ��
        char lowerChar = (str[i] <= 'Z') ? str[i] + 32 : str[i];
        alphabet[lowerChar - 'a'][1]++;
        i++;
    }
    //����ĸʹ��Ƶ�ʴӴ�С����
    sort(alphabet.begin(), alphabet.end(), comp);
    //������
    for (int j = 0; j < 26; j++) {
        if (alphabet[j][1] == 0) {    //û�г��ֵ���ĸ�����
            break;
        }
        cout << "��ĸ" << (char) alphabet[j][0]
             << "������" << alphabet[j][1] << "��" << endl;
    }
    return 0;
}

/*==============================================
�Ƚ�������ĸ����Ƶ�ʴ�С(>)����sort��������
����˵����
	������Ϊvector<int>�ĳ����ã�1��Ԫ��Ϊ����Ƶ��
����ֵ˵����
	true����left������ĸ����Ƶ�ʴ���right������ĸ
	false����left������ĸ����Ƶ�ʲ�����right������ĸ
==============================================*/
bool comp(const vector<int> &left, const vector<int> &right) {
    return (left[1] > right[1]);
}
