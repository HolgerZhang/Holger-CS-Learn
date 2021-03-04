#include <iostream>
#include <iomanip>
using namespace std;

class CComplex {
public:
	// 带缺省参数的构造函数（可以避免重载）
	CComplex(double real = 0, double image = 0) {
		m_real = real;
		m_image = image;
		m_count++;
	}

	CComplex(const CComplex& other) {
		m_real = other.m_real;
		m_image = other.m_image;
		m_count++;
	}

	~CComplex() {
		m_count--;
	}

	static int getCount() {
		//m_real++;
		return m_count;
	}

	static int getSum(const CComplex& self) {	// static方法访问非静态成员
		return self.m_real + self.m_image;
	}

	void show() {
		cout << m_real << setiosflags(ios::showpos) << m_image 
			 << resetiosflags(ios::showpos) << "*j" << endl;
	}

	CComplex operator+(const CComplex& temp) const {
		return CComplex(m_real + temp.m_real, m_image + temp.m_image);
	}

	CComplex operator+(double temp) const {
		return CComplex(m_real + temp, m_image);
	}

	CComplex add(const CComplex& temp) const {
		return CComplex(m_real + temp.m_real, m_image + temp.m_image);
	}

	CComplex add(double temp) const {
		return CComplex(m_real + temp, m_image);
	}

	// 后置++
	CComplex operator++(int) {
		CComplex backup(*this);
		m_real++;
		m_image++;
		return backup;
	}

	// 前置++
	CComplex& operator++() {
		m_real++;
		m_image++;
		return (*this);
	}

	friend CComplex operator+(double temp, const CComplex& self);

	friend CComplex& operator--(CComplex& self);
	friend CComplex operator--(CComplex& self, int);
	friend ostream& operator<<(ostream& out, const CComplex& self);

private:
	double m_real;
	double m_image;
	static int m_count;
};

int CComplex::m_count = 0;

int main() {
	cout << CComplex::getCount() << endl;
	CComplex c1(3.5, 1.7);
	cout << c1.getCount() << endl;
	cout << c1 << endl;
	CComplex c2(c1);
	cout << c2.getCount() << endl;
	cout << c2 << endl;
	CComplex c3 = c2--, c4 = --c1;
	cout << c3.getCount() << endl;
	cout << c3 << endl;
	cout << c4.getCount() << endl;
	cout << c4 << endl;
	return 0;
}

CComplex operator+(double temp, const CComplex& self) {
	return CComplex(self.m_real + temp, self.m_image);
}

CComplex& operator--(CComplex& self) {
	self.m_real--;
	self.m_image--;
	return self;
}

CComplex operator--(CComplex& self, int) {
	CComplex backup(self);
	--self;
	return backup;
}

ostream& operator<<(ostream& out, const CComplex& self) {
	out << self.m_real << setiosflags(ios::showpos) << self.m_image
		<< resetiosflags(ios::showpos) << "*j";
	return out;
}
