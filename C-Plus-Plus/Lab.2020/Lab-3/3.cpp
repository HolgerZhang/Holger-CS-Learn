/**
 * @file    3.cpp
 * @create  2020/03/18
 * @encoding GBK
 * @author  Holger
 * @description
 * 实验三 数据类型和数组
 *  用手机发短信，一条短信资费为0.1元，但限定一条短信的内容在70个字以内
 *  （包括70个字）。如果你一次所发送的短信超过了70个字，则会按照每70个字
 *  一条短信的限制把它分割成多条短信发送。
 *  假设如下数组存储了一个人一个月发送的每个短信的分别字数
 *  int arry [12] = {35,146,57,13,224,35,99,68,113,79,88,46}，
 *  试统计一下他当月短信的总资费。
 */

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    //一个人每个月发送的每个短信的分别字数
    int arry[12] = {35, 146, 57, 13, 224, 35, 99, 68, 113, 79, 88, 46};
    int numbers = 0;    //发送的短信的条数
    for (int i = 0; i < 12; i++) {
        numbers += (int) ceil(arry[i] / 70.0);    //每个信息对应条数，向上取整
    }
    cout << "他当月短信的总资费为" << numbers * 0.1 << "元。" << endl;
    return 0;
}