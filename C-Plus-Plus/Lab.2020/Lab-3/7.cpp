/**
 * @file    3.cpp
 * @create  2020/03/18
 * @encoding GBK
 * @author  Holger
 * @description
 * 实验三 数据类型和数组
 * 手工在程序所在目录下创建1个文本文件Data.txt，该文件中存放了9个int数据，
 * 各数据之间以空格间隔。编写1个程序，使用文件流的相关方法顺序完成以下操作：
 *  - 读取文件Data.txt中的所有数据；
 *  - 将读取得到的数据以二进制的形式存放到程序所在目录下的文件Res.dat中；
 *  - 再次读取Res.dat中的所有数据；
 *  - 并将这些数据以文本文件的形式存放到程序所在目录下的Res.txt文件中，
 *    存放时每行2个数据，每个数据占10列，右对齐，左边补'C'字符。
 */

#include <iostream>
#include <fstream>
#include <iomanip>

#define N 9            //整数的个数：9
using namespace std;

int main() {
    int nums_from_text[N];    //从Data.txt读取的N个整数

    //文本文件输入流，从Data.txt读取
    ifstream inTextFile("Data.txt", ios_base::in);
    //读取N个int数据
    for (int i = 0; i < N; i++) {
        inTextFile >> nums_from_text[i];
    }
    inTextFile.close(); //关闭Data.txt
    cout << "读取文件Data.txt完成。" << endl;

    //二进制文件输出流，向Res.dat写入
    ofstream outBinFile("Res.dat", ios_base::out | ios_base::binary);
    //以二进制的形式写入N个int数据
    for (int i = 0; i < N; i++) {
        outBinFile.write((char *) (&nums_from_text[i]), sizeof(int));
    }
    outBinFile.close(); //关闭Res.dat
    cout << "写入文件Res.dat完成。" << endl;

    int nums_from_bin[N];    //从Res.dat读取的N个整数

    //二进制文件输入流，从Res.dat读取
    ifstream inBinFile("Res.dat", ios_base::in | ios_base::binary);
    //读取N个二进制的int数据
    for (int i = 0; i < N; i++) {
        inBinFile.read((char *) (&nums_from_bin[i]), sizeof(int));
    }
    inBinFile.close();    //关闭Res.dat
    cout << "读取文件Res.dat完成。" << endl;

    //文本文件输出流，向Res.txt写入
    ofstream outTextFile("Res.txt", ios_base::out);
    //读取N个int数据
    for (int i = 0; i < N; i++) {
        //每行2个数据，每个数据占10列，右对齐，左边补'C'字符
        outTextFile << setiosflags(ios_base::right);
        outTextFile << setw(10) << setfill('C') << nums_from_bin[i];
        if ((i + 1) % 2 == 0) {
            outTextFile << endl;
        }
    }
    outTextFile.close(); //关闭Res.txt
    cout << "写入文件Res.txt完成。" << endl;

    return 0;
}
