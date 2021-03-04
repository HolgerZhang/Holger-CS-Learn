/**
 * @file    3.cpp
 * @create  2020/03/18
 * @encoding GBK
 * @author  Holger
 * @description
 * ʵ���� �������ͺ�����
 * �ֹ��ڳ�������Ŀ¼�´���1���ı��ļ�Data.txt�����ļ��д����9��int���ݣ�
 * ������֮���Կո�������д1������ʹ���ļ�������ط���˳��������²�����
 *  - ��ȡ�ļ�Data.txt�е��������ݣ�
 *  - ����ȡ�õ��������Զ����Ƶ���ʽ��ŵ���������Ŀ¼�µ��ļ�Res.dat�У�
 *  - �ٴζ�ȡRes.dat�е��������ݣ�
 *  - ������Щ�������ı��ļ�����ʽ��ŵ���������Ŀ¼�µ�Res.txt�ļ��У�
 *    ���ʱÿ��2�����ݣ�ÿ������ռ10�У��Ҷ��룬��߲�'C'�ַ���
 */

#include <iostream>
#include <fstream>
#include <iomanip>

#define N 9            //�����ĸ�����9
using namespace std;

int main() {
    int nums_from_text[N];    //��Data.txt��ȡ��N������

    //�ı��ļ�����������Data.txt��ȡ
    ifstream inTextFile("Data.txt", ios_base::in);
    //��ȡN��int����
    for (int i = 0; i < N; i++) {
        inTextFile >> nums_from_text[i];
    }
    inTextFile.close(); //�ر�Data.txt
    cout << "��ȡ�ļ�Data.txt��ɡ�" << endl;

    //�������ļ����������Res.datд��
    ofstream outBinFile("Res.dat", ios_base::out | ios_base::binary);
    //�Զ����Ƶ���ʽд��N��int����
    for (int i = 0; i < N; i++) {
        outBinFile.write((char *) (&nums_from_text[i]), sizeof(int));
    }
    outBinFile.close(); //�ر�Res.dat
    cout << "д���ļ�Res.dat��ɡ�" << endl;

    int nums_from_bin[N];    //��Res.dat��ȡ��N������

    //�������ļ�����������Res.dat��ȡ
    ifstream inBinFile("Res.dat", ios_base::in | ios_base::binary);
    //��ȡN�������Ƶ�int����
    for (int i = 0; i < N; i++) {
        inBinFile.read((char *) (&nums_from_bin[i]), sizeof(int));
    }
    inBinFile.close();    //�ر�Res.dat
    cout << "��ȡ�ļ�Res.dat��ɡ�" << endl;

    //�ı��ļ����������Res.txtд��
    ofstream outTextFile("Res.txt", ios_base::out);
    //��ȡN��int����
    for (int i = 0; i < N; i++) {
        //ÿ��2�����ݣ�ÿ������ռ10�У��Ҷ��룬��߲�'C'�ַ�
        outTextFile << setiosflags(ios_base::right);
        outTextFile << setw(10) << setfill('C') << nums_from_bin[i];
        if ((i + 1) % 2 == 0) {
            outTextFile << endl;
        }
    }
    outTextFile.close(); //�ر�Res.txt
    cout << "д���ļ�Res.txt��ɡ�" << endl;

    return 0;
}
