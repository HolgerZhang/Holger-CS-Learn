/**
 * @file E01.cpp
 * @create 2020-06-28 22:00
 * @encoding UTF-8
 * @author Holger
 * @description 请为Cline函数补充必要的成员函数与实现代码，使得程序正确运行。
 * @result
 *      Point 1 is:(0,0)
 *      Point 2 is:(0,0)
 *      Length=0
 *      Point 1 is:(1,1)
 *      Point 2 is:(5,5)
 *      Length=5.65685
 **/

#include <iostream>
#include <cmath>

using namespace std;

class CPoint {
    int m_x; //点的X坐标
    int m_y; //点的Y坐标
public:
    CPoint() {
        m_x = 0;
        m_y = 0;
    }

    CPoint(int x, int y) {
        m_x = x;
        m_y = y;
    }

    int getx() {
        return m_x;
    }

    int gety() {
        return m_y;
    }

    void showPoint() {
        cout << "(" << this->m_x << "," << this->m_y << ")" << endl;
    }
};

class CLine {
    CPoint m_point1;
    CPoint m_point2;
public:
    CLine() : m_point1(), m_point2() {}

    CLine(int point1_x, int point1_y, int point2_x, int point2_y)
            : m_point1(point1_x, point1_y), m_point2(point2_x, point2_y) {}

    double distance() {
        return sqrt(pow(m_point1.getx() - m_point2.getx(), 2) + pow(m_point1.gety() - m_point2.gety(), 2));
    }

    void ShowLine() {
        cout << "Point 1 is:";
        m_point1.showPoint();
        cout << "Point 2 is:";
        m_point2.showPoint();
    }
};

int main() {
    CLine line1;
    line1.ShowLine();
    cout << "Length=" << line1.distance() << endl;

    CLine line2(1, 1, 5, 5);
    line2.ShowLine();
    cout << "Length=" << line2.distance() << endl;

    return 0;
}
