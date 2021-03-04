#include <iostream>
#include <cmath>
using namespace std;

class Circle {
public:
    Circle(double x, double y, double r): x(x), y(y), r(r) {
        num = ++max_num;
        total_num++;
    }

    Circle(const Circle& other): x(other.x), y(other.y), r(other.r) {
        num = ++max_num;
        total_num++;
    }

    ~Circle() {
        total_num--;
    }

    static int get_num() {
        return total_num;
    }

    double area() const { return (PI * r * r); }

    double circumference() const { return (2 * PI * r); }

    Circle& operator++() {
        r++;
        return *this;
    }

    Circle operator++(int) {
        Circle backup(*this);
        ++(*this);
        return backup;
    }

    Circle operator+(const Circle& other) const {
        return Circle((this->x + other.x) / 2,
                      (this->y + other.y) / 2,
                      sqrt((this->area() + other.area()) / PI));
    }

    friend ostream& operator<<(ostream& out, const Circle& self);

private:
    double x;
    double y;
    double r;
    int num;
    static int max_num;
    static int total_num;
    static const double PI;
};

ostream& operator<<(ostream& out, const Circle& self) {
    out << "Circle " << self.num << " ,x = " << self.x << " ,y = " << self.y << " ,r = " << self.r << " ,area: "
        << self.area() << " ,circumference: " << self.circumference() << endl;
    return out;
}

int Circle::total_num = 0;
int Circle::max_num = 0;
const double Circle::PI = 3.14159;

int main() {
    Circle c1(1.12, 2.23, 3.34), c2(c1);

    cout << c1 << c2;
    cout << "Number of circles = " << Circle::get_num() << endl;

    Circle c3 = c1 + c2;
    cout << c3;
    cout << "Number of circles = " << Circle::get_num() << endl;

    cout << c1++;
    cout << ++c2;
    cout << c1;

    return 0;
}
