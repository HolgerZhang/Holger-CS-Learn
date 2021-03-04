#include <iostream>

using namespace std;

class CMyArray {
private:
	int* m_p;
	int m_size;

public:
	CMyArray(int size) {
		m_size = size;
		m_p = new int[m_size + 1];
		memset(m_p, 0, sizeof(int) * (m_size + 1));
	}
	~CMyArray() {
		if (m_p) {
			delete[] m_p;
		}
	}
	int &operator[](int pos) {
		if (pos < 0 || pos >= m_size) {
			//throw out_of_range("index out of range.");
			cout << "index out of range" << endl;
			return m_p[m_size];
		}
		return m_p[pos];
	}
};

int main() {
	CMyArray array1(50);
	array1[2] = 5;
	cout << array1[2] << endl;
	cout << array1[50] << endl;
	return 0;
}