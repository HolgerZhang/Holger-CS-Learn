/**
 * @file    E01.cpp
 * @create  2020/05/04
 * @encoding UTF-8
 * @author  Holger
 * @description
 * 实验六 运算符重载、静态成员
 * E01.	在E22圆形类的基础上，完成如下功能：
 *    - 定义加法运算，规则：两圆之和为一个新的圆，圆心是第一个操作数的圆心（如a+b，则a的圆心为a+b的圆心），半径为两圆半径之和。加法运算不改变操作数。
 *    - 定义减法运算，规则：两圆之差为一个新的圆，圆心是第一个操作数的圆心，面积为两圆面积之差的绝对值。减法运算不改变操作数。
 *    - 定义自增、自减运算（含前、后自增），对半径进行自增、自减运算。
 *    - 定义输出流运算，输出圆心坐标、半径、周长、面积。
 *    - 定义>、<运算，比较两圆面积之间的大小关系。
 *    - 定义==、!=运算，比较两圆是否是完全相同的圆，当两个圆的圆心坐标和半径完全一致时则两圆完全相同。
 *    - 定义&运算，确定两圆是否同心。
 *    - 定义|运算，确定两圆的位置关系（相交、相切、相离、包含）。
 *    - 编写主函数，任意生成若干圆，分别测试上述功能。
 */
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// 表示圆形的 Circle 类
class Circle {
private:
    static const double pi; // 圆周率

    double x;              // x坐标
    double y;              // y坐标
    double radius;         // 半径
    double circumference;  // 周长
    double area;           // 面积

public:

    enum class position_type {    // 位置关系：相交, 相切, 相离, 包含
        intersect, tangent, separate, contain
    };

    // 构造函数
    Circle(double x = 0.0, double y = 0.0, double r = 0.0) : x(x), y(y), radius(r) {
        circumference = pi * radius * 2.0;
        area = pi * radius * radius;
    }

    // 设置圆心坐标
    void setPosition(double x, double y) {
        this->x = x;
        this->y = y;
    }

    // 设置半径
    void setRadius(double r) {
        radius = r;
        circumference = pi * radius * 2.0;
        area = pi * radius * radius;
    }

    // 获取圆的面积
    double getArea() const { return area; }

    // 获取圆的周长
    double getCircumference() const { return circumference; }

    // 加法运算：两圆之和为一个新的圆，圆心是第一个操作数的圆心，半径为两圆半径之和，不改变操作数
    Circle operator+(const Circle &temp) const {
        return Circle(x, y, radius + temp.radius);
    }

    // 减法运算：两圆之差为一个新的圆，圆心是第一个操作数的圆心，面积为两圆面积之差的绝对值，不改变操作数
    Circle operator-(const Circle &temp) const {
        return Circle(x, y, abs(radius - temp.radius));
    }

    // 对半径进行前自增运算
    Circle &operator++() {
        radius++;
        return (*this);
    }

    // 对半径进行后自增运算
    Circle operator++(int) {
        Circle backup(*this);
        ++(*this);
        return backup;
    }

    // 对半径进行前自减运算
    Circle &operator--() {
        radius--;
        return (*this);
    }

    // 对半径进行后自减运算
    Circle operator--(int) {
        Circle backup(*this);
        --(*this);
        return backup;
    }

    // 比较两圆面积之间的大小关系（定义>、<运算）
    bool operator<(const Circle &temp) const { return (this->area < temp.area); }
    bool operator>(const Circle &temp) const { return (this->area > temp.area); }

    // 定义&运算，确定两圆是否同心
    bool operator&(const Circle &temp) const {
        return ((this->x == temp.x) && (this->y == temp.y));
    }

    // 比较两圆是否是完全相同的圆（圆心坐标和半径完全一致）（定义==、!=运算）
    bool operator==(const Circle &temp) const {
        return ((*this & temp) && (this->radius == temp.radius));
    }
    bool operator!=(const Circle &temp) const { return !(*this == temp); }

    // 定义|运算，确定两圆的位置关系（相交、相切、相离、包含）
    position_type operator|(const Circle &temp) const;

    // 输出圆心坐标、半径、周长、面积
    friend ostream &operator<<(ostream &out, const Circle &circle);
};

const double Circle::pi = 3.14159;

// 定义|运算，确定两圆的位置关系（相交、相切、相离、包含）
Circle::position_type Circle::operator|(const Circle &temp) const {
    Circle::position_type position;
    double distance = sqrt(pow((this->x - temp.x), 2) + pow((this->y - temp.y), 2));
    if (distance > this->radius + temp.radius) {    // 相离
        position = position_type::separate;
    } else if ((distance < this->radius + temp.radius) &&
        (distance > abs(this->radius - temp.radius))) {     // 相交
        position = position_type::intersect;
    } else if (distance < abs(this->radius - temp.radius)) {    // 包含
        position = position_type::contain;
    } else {    // 其他条件：相切
        position = position_type::tangent;
    }
    return position;
}

// 输出圆心坐标、半径、周长、面积
ostream &operator<<(ostream &out, const Circle &circle) {
    out << "centre: (" << circle.x << "," << circle.y
        << ")\tradius = " << circle.radius << "\tcircumference = "
        << circle.circumference << "\tarea = " << circle.area;
    return out;
}


// 主函数
int main() {
    Circle circles[5] = {
            Circle(2, 0, 2),
            Circle(0, 0, 1),
            Circle(2, 0, 1),
            Circle(2, 1, 1),
            Circle(5, 5, 0.5)
    };
    cout << "Here are 5 Circle object:" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << "Circle" << i << ": " << circles[i] << endl;
    }
    cout << endl;

    Circle c1 = circles[0] + circles[1];
    cout << "Circle0 + Circle1 = Circle: " << c1 << endl;
    Circle c2 = circles[4] - circles[1];
    cout << "Circle4 - Circle1 = Circle: " << c2 << endl;
    cout << endl;

    cout << setiosflags(ios::boolalpha);
    cout << "Does the area of Circle1 larger than that of Circle0? "
         << (circles[1] > circles[0]) << endl;
    cout << "Does the area of Circle1 larger than that of Circle4? "
         << (circles[1] > circles[4]) << endl;
    cout << "Does the area of Circle2 smaller than that of Circle0? "
         << (circles[2] < circles[0]) << endl;
    cout << "Does the area of Circle2 smaller than that of Circle4? "
         << (circles[2] < circles[4]) << endl;
    cout << endl;

    cout << "Circle0: " << circles[0] << endl;
    cout << "Circle2: " << circles[2] << endl;
    cout << "(++circles[2] == circles[0])? "
         << (++circles[2] == circles[0]) << endl;
    cout << "Now Circle2: " << circles[2] << endl;
    cout << "circles[2]-- is Circle: " << circles[2]-- << endl;
    cout << "Now Circle2: " << circles[2] << endl;
    cout << "(circles[2] != circles[0]--)? "
         << (circles[2] != circles[0]--) << endl;
    cout << "Now Circle0: " << circles[0] << endl;
    cout << "++circles[0] is Circle: " << ++circles[0] << endl;
    cout << "Now Circle0: " << circles[0] << endl;
    cout << endl;

    for (int j = 1; j < 5; ++j) {
        cout << "The location relationship between Circle0 and Circle" << j << " is ";
        switch (circles[0] | circles[j]) {
            case Circle::position_type::separate:
                cout << "separate.";
                break;
            case Circle::position_type::intersect:
                cout << "intersect.";
                break;
            case Circle::position_type::contain:
                cout << "contain.";
                break;
            case Circle::position_type::tangent:
                cout << "tangent.";
                break;
        }
        cout << endl;
    }

    return 0;
}