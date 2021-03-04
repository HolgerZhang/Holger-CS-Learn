/**
 * @file    E05.cpp
 * @create  2020/03/03
 * @encoding GBK
 * @author  Holger
 * @description
 *  在苏大校园里,没有自行车,上课办事会很不方便.但实际上,并非去办任何事情都是骑车快,
 *  因为骑车总要找车、开锁、停车、锁车等,这要耽误一些时间。
 *  假设找到自行车、开锁并骑上自行车的时间为27秒；停车锁车的时间为23秒；
 *  步行每秒行走1.2米,骑车每秒行走3.0米。
 *  请判断走不同的距离去办事,是骑车快还是走路快。
 *  程序的输入是一个整数表示距离，单位是米，
 *  如果计算结果是步行快，请输出“步行快”，如果计算结果是骑车快，请输出“骑车快”，否则输出“一样快”。
 */
#include <iostream>

using namespace std;

int main() {
    int distance;        //距离（单位：米）
    cout << "请输入距离：";
    cin >> distance;
    //骑车需要的时间
    double riding = 50 + distance / 3.0;
    //步行需要的时间
    double walking = distance / 1.2;
    //判断是否相等
    if (abs(riding - walking) < 1e-5) {
        cout << "一样快" << endl;
    }
        //判断骑车和步行需要的时间哪个更大
    else {
        if (riding > walking)
            cout << "骑车快" << endl;
        else
            cout << "步行快" << endl;
    }
    return 0;
}