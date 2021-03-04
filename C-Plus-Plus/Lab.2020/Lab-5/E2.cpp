/**
 * @file    E2.cpp
 * @create  2020/05/04
 * @encoding UTF-8
 * @author  Holger
 * @description
 * 实验五 类与对象
 * E2.  设计一个类 Column，表示圆柱体。设圆柱体底面在 Z=0 的平面内。
 *      - Column类以底面圆（参见E1题）和高来确定圆柱体。
 *      - Column类具有如下方法：
 *          i.   可设置底面圆心。
 *          ii.  可设置底面半径。
 *          iii. 可设置高。
 *          iv.  可计算底面积。
 *          v.   可计算底面的周长。
 *          vi.  可计算侧面积。
 *          vii. 可计算体积。
 *      编写主函数，测试类的功能。
 */

#include <iostream>

using namespace std;
const double pi = 3.14159;  // 圆周率

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
    void setRadius(double r) { radius = r; }

    // 计算圆的面积
    double getArea() const { return (pi * radius * radius); }

    // 计算圆的周长
    double getCircumference() const { return (pi * radius * 2); }

    // 测试用：显示圆基本信息
    void show() const {
        cout << "Circle object at (" << centre.x << ","
             << centre.y << "), radius is " << radius;
    }
};

const double Circle::pi = 3.14159;

// 表示圆柱体的 Column 类
class Column {
private:
    Circle circle;
    double height;

public:
    // 设置底面圆心坐标
    void setCirclePosition(double x, double y) {
        circle.setPosition(x, y);
    }

    // 设置底面半径
    void setCircleRadius(double r) {
        circle.setRadius(r);
    }

    // 设置高
    void setHeight(double h) { height = h; }

    // 计算底面圆的面积
    double getBottomArea() const {
        return circle.getArea();
    }

    // 计算底面圆的周长
    double getBottomCircumference() const {
        return circle.getCircumference();
    }

    // 计算侧面积
    double getSideArea() const {
        return (circle.getCircumference() * height);
    }

    // 计算体积
    double getVolume() const {
        return (circle.getArea() * height);
    }

    // 测试用：显示圆柱基本信息
    void show() const {
        cout << "Column object, bottom in plane Z=0: Bottom ";
        circle.show();
        cout << ", height is " << height << endl;
    }
};

// 主函数
int main() {
    Column column;
    column.setCirclePosition(1.5, 3.5);   // 设置圆心坐标为(1.5,3.5)
    column.setCircleRadius(2.8);          // 设置底面半径为2.8
    column.setHeight(9.2);                // 设置高为9.2
    column.show();                        // 显示圆柱基本信息

    cout << "The area of bottom: " << column.getBottomArea() << endl;    // 底面面积
    cout << "The circumference: " << column.getBottomCircumference() << endl;  // 底面周长
    cout << "The area of side: " << column.getSideArea() << endl;  // 侧面积
    cout << "The volume of column: " << column.getVolume() << endl;  // 体积
    return 0;
}
