#include <iostream>

using namespace std;

class CCircle {
public:
    CCircle(double x, double y, double r) : m_x(x), m_y(y), m_radius(r) {}

    double area() const {
        return (PI * m_radius * m_radius);
    }

    double circumference() const {
        return (PI * m_radius * 2);
    }

    double getX() const {
        return m_x;
    }

    double getY() const {
        return m_y;
    }

    double getRadius() const {
        return m_radius;
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
    CCylinder(double x, double y, double r, double h) : CCircle(x, y, r), m_h(h) {}

    void setH(double h) {
        m_h = h;
    }

    double getH() const {
        return m_h;
    }

    double getFloorArea() const { return area(); }


    double volume() const {
        return (area() * m_h);
    }

};

int main() {
    CCylinder shape1(1, 2, 2, 4);
    cout << shape1.volume() << endl;
    cout << shape1.area() << endl;
}