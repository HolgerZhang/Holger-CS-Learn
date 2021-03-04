/**
 * @file    E02.cpp
 * @create  2020/05/04
 * @encoding UTF-8
 * @author  Holger
 * @description
 * 实验六 运算符重载、静态成员
 * E02.	设有描述复数的类CComplex定义：
 *      请使用友元函数实现如下重载：
 *      - 重载<<运算符，使得可以用cout<<输出复数，每个复数输出的格式为： “实部+虚部*i”;
 *      - 重载+运算符，使得可以实现两个复数相加；
 *      - 重载+运算符，使得可以实现复数和实数的相加；
 *      - 重载前置++运算符，使得可以实现复数的实部和虚部分别加1；
 *      - 重载后置++运算符，使得可以实现复数的实部和虚部分别加1；
 *      - 在main函数中测试并试用这些运算符。
 */

#include <iostream>
#include <iomanip>

using namespace std;

// 复数的类CComplex定义
class CComplex {
    double m_real;
    double m_image;
public:
    void setValue(double real, double image) {
        m_real = real;
        m_image = image;
    }
    // 友元函数声明
    friend ostream &operator<<(ostream &out, const CComplex &self);
    friend CComplex operator+(const CComplex &left, const CComplex &right);
    friend CComplex operator+(const CComplex &left, int right);
    friend CComplex operator+(int left, const CComplex &right);
    friend CComplex &operator++(CComplex &self);
    friend CComplex operator++(CComplex &self, int);
};

// 重载<<运算符，使得可以用cout<<输出复数
ostream &operator<<(ostream &out, const CComplex &self) {
    out << self.m_real << setiosflags(ios::showpos) << self.m_image << "*i";
    out << resetiosflags(ios::showpos);
    return out;
}

// 重载+运算符，使得可以实现两个复数相加
CComplex operator+(const CComplex &left, const CComplex &right) {
    CComplex result;
    result.setValue(left.m_real + right.m_real, left.m_image + right.m_image);
    return result;
}

// 重载+运算符，使得可以实现复数和实数的相加
CComplex operator+(const CComplex &left, int right) {
    CComplex result;
    result.setValue(left.m_real + right, left.m_image);
    return result;
}

// 重载+运算符，使得可以实现实数和复数的相加
CComplex operator+(int left, const CComplex &right) {
    return (right+left);
}

// 重载前置++运算符，使得可以实现复数的实部和虚部分别加1
CComplex &operator++(CComplex &self) {
    self.m_real++;
    self.m_image++;
    return self;
}

// 重载后置++运算符，使得可以实现复数的实部和虚部分别加1
CComplex operator++(CComplex &self, int) {
    CComplex backup(self);
    ++self;
    return backup;
}

// 主函数
int main() {
    CComplex c1, c2;
    c1.setValue(1, -5);
    c2.setValue(2, 3);
    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;

    cout << "c1 + c2 = " << c1 + c2 << endl;
    cout << "c1 + 2 = " << c1 + 2 << endl;
    cout << "-2 + c2 = " << -2 + c2 << endl;
    cout << "c1++ = " << c1++ << endl;
    cout << "Now: c1 = " << c1 << endl;
    cout << "++c2 = " << ++c2 << endl;
    cout << "Now: c2 = " << c2 << endl;

    return 0;
}
