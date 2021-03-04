#include<iostream>
#include<string>
using namespace std;


class CMyStack {
private:
	char m_buff[100];
	int m_top;

public:
	CMyStack() {
		m_top = -1;
	}

	bool push(char ch) {
		if (isFull()) {
			return false;
		}
		m_top++;
		m_buff[m_top] = ch;
		return true;
	}

	bool pop(char& ch) {
		if (isEmpty()) {
			return false;
		}
		ch = m_buff[m_top];
		m_top--;
		return true;
	}

	bool isEmpty() { return (m_top == -1); }

	bool isFull() { return (m_top >= 99); }
};



bool match(string& str) {
	CMyStack stack;
	char ch1 = 0;
	for (auto& ch : str) {
		switch (ch) {
		case '(': case '{':
			stack.push(ch);
			break;
		case ')':
			if (!stack.pop(ch1)) {
				return false;
			}
			if (ch1 != '(') {
				return false;
			}
			break;
		case '}':
			if (!stack.pop(ch1)) {
				return false;
			}
			if (ch1 != '{') {
				return false;
			}
			break;
		}
	}
	return true;
}

int main() {
	string code;
	cout << "Please input an expression: ";
	cin >> code;
	if (match(code)) {
		cout << "TRUE" << endl;
	}
	else {
		cout << "FALSE" << endl;
	}
	return 0;
}