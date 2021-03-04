/**
 * @file    E1.cpp
 * @create  2020/05/04
 * @encoding UTF-8
 * @author  Holger
 * @description
 * 实验五 类与对象
 * E1.  设计一个类 Circle ，表示圆形。
 *      - Circle 类以圆心坐标 (x,y) 和半径 r 来确定圆。
 *      - Circle 类具有如下方法：
 *          i.   可设置圆心坐标。
 *          ii.  可设置半径。
 *          iii. 可计算圆的面积。
 *          iv.  可计算圆的周长。
 *      编写主函数，测试类的功能。
 */

#include <iostream>

using namespace std;

// 表示xOy平面上的一个点
struct Point {
    double x;   // x坐标
    double y;   // y坐标
};

// 表示圆形的 Circle 类
class Circle {
private:
    double radius; // 半径
    Point centre; // 圆心坐标
    static const double pi;  // 圆周率

public:
    // 设置圆心坐标
    void setPosition(double x, double y) {
        centre.x = x;
        centre.y = y;
    }

    // 设置半径
    void setRadius(double r) {
        radius = r;
    }

    // 计算圆的面积
    double getArea() const {
        return (pi * radius * radius);
    }

    // 计算圆的周长
    double getCircumference() const {
        return (pi * radius * 2);
    }

    // 测试用：显示圆基本信息
    void show() const {
        cout << "Circle object at (" << centre.x << ","
             << centre.y << "), radius is " << radius << endl;
    }
};

const double Circle::pi = 3.14159;

// 主函数
int main() {
    Circle circle;
    circle.setPosition(2.0, -5.3);    // 设置圆心坐标为(2,-3.5)
    circle.setRadius(3.5);            // 设置半径为3.5
    circle.show();                    // 显示圆基本信息

    // 计算周长和面积
    cout << "Area is " << circle.getArea() << "; "
         << "circumference is " << circle.getCircumference() << endl;
    return 0;
}
