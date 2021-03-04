#include <iostream>

using namespace std;

class CCircle {
public:
    CCircle(double x, double y, double r) : m_x(x), m_y(y), m_radius(r) {
        // cout << "1 CCircle constructor called." << endl;
    }

    double area() const { return (PI * m_radius * m_radius); }

    double circumference() const { return (PI * m_radius * 2); }

    double getX() const { return m_x; }

    double getY() const { return m_y; }

    double getRadius() const { return m_radius; }

    ~CCircle() {
        // cout << "3 CCircle destructor called." << endl;
    }

    void show() const {
        cout << "method 'show' of class CCircle" << endl;
        cout << "at (" << m_x << ", " << m_y << ") ,r = " << m_radius;
    }

private:
    double m_x;
    double m_y;
    double m_radius;
    static const double PI;
};


const double CCircle::PI = 3.14159;


class CCylinder : public CCircle {
private:
    double m_h;
public:
    CCylinder(double x, double y, double r, double h) : CCircle(x, y, r), m_h(h) {
        // cout << "2 CCylinder constructor called." << endl;
    }

    void setH(double h) { m_h = h; }

    double getH() const { return m_h; }

    double getFloorArea() const { return area(); }

    ~CCylinder() {
        // cout << "4 CCylinder destructor called." << endl;
    }

    double volume() const { return (area() * m_h); }

    void show() const {
        // CCircle::show();
        cout << "method 'show' of class CCylinder" << endl;
        cout << ", h = " << m_h;
    }

};


// class A {
// public:
//     int a;
//     A(int num): a(num) {}
// };
//
// class B1 : virtual public A {
// public:
//     int b;
//     B1(int num1, int num2): A(num1), b(num2) { }
// };
//
// class B2 : virtual public A {
// public:
//     int b;
//     B2(int num1, int num2) : A(num1), b(num2) { }
// };
//
// class C : public B1, public B2 {
// public:
//     C(int num1, int num2, int num3, int num4, int num5): A(num1), B1(num2, num3), B2(num4, num5) {}
// };

int main() {
    // CCircle circle(1, 2, 3);
    // circle.show();
    // cout << endl;
    CCylinder cylinder(1, 2, 2, 4);
    cylinder.CCircle::show();
	// C cobj(1, 2, 3, 4, 5);
	// cout << cobj.a << endl;
	// cout << cobj.B1::b << endl;
	// cout << cobj.B2::b << endl;

    return 0;
}
