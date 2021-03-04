
#include <iostream>
using namespace std;

class CA {
private:
	int m_x;
public:
	void setX(int x) {
		m_x = x;
	}
	int getX() const {
		return m_x;
	}
	void show() const {
        cout << m_x << endl;
	}
};

class CB : public CA {
private:
	int m_y;
public:
	void setY(int y) {
		m_y = y;
	}
	int getY() const {
		return m_y;
	}
	void show() const {
		cout << m_y << endl;
	}
};

int main() {
	CA a1;
	CB b1;
	// a1 = b1;
	// b1 = a1;
	a1.setX(2);
	b1.setX(6);
	b1.setY(3);
	CA& ref = b1;
	// ref.show();
	CA* p = &b1;
	p->show();
    return 0;
}