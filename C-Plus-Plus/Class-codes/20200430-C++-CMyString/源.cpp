#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <cstring>
using namespace std;

class CMyString {
public:
	// 默认构造函数
	CMyString() {
		m_p = 0;
		m_len = 0;
	}
	// 带一个参数的构造函数
	CMyString(char* p) {
		m_len = strlen(p);
		m_p = new char[m_len + 1];
		strcpy(m_p, p);
	}
	// 拷贝构造函数
	CMyString(const CMyString& temp) {
		if (temp.m_p == 0) {
			m_p = 0;
			m_len = 0;
		}
		else {
			m_len = temp.m_len;
			m_p = new char[m_len + 1];
			strcpy(m_p, temp.m_p);
		}
	}
	void setString(char* p) {
		if (m_p) {
			delete[] m_p;
		}
		m_len = strlen(p);
		m_p = new char[m_len + 1];
		strcpy(m_p, p);
	}
	void show() const {
		if (m_p) {
			cout << m_p << endl;
		}
	}
	int getLength() const {
		return m_len;
	}
/*	CMyString operator+(const CMyString& temp) const {
		char* str = new char[m_len + temp.m_len + 1];
		strcpy(str, "");
		strcat(str, m_p);
		strcat(str, temp.m_p);
		CMyString res(str);
		delete[] str;
		return res;
	}*/

	CMyString operator+(const CMyString& temp) const {
		CMyString res;
		if (!(m_p || temp.m_p)) {
			return res;
		}
		res.m_len = m_len + temp.m_len;
		res.m_p = new char[res.m_len + 1];
		strcpy(res.m_p, "");
		if(m_p)
			strcat(res.m_p, m_p);
		if(temp.m_p)
			strcat(res.m_p, temp.m_p);
		return res;
	}

	CMyString operator=(const CMyString& temp) {
		if (m_p) {
			delete[] m_p;
		}
		if (temp.m_p == 0) {
			m_p = 0;
			m_len = 0;
		}
		else {
			m_len = temp.m_len;
			m_p = new char[m_len + 1];
			strcpy(m_p, temp.m_p);
		}
		return CMyString(*this);
	}
	// 析构函数
	~CMyString() {
		if (m_p) {
			delete[] m_p;
		}
	}
private:
	char* m_p;
	int m_len;
};


int main() {
	CMyString str1("3");
	str1.show();
	CMyString str2;
	str2.show();
	CMyString str3("1");
	str3 = str1 + str2;
	str3.show();
	return 0;
}