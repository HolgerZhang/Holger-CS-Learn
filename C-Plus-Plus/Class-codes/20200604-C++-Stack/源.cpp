#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int MaxStackSize = 50;

template <class T>
class Stack {
private:
    T stacklist[MaxStackSize];
    int m_top;
public:
    Stack(void);
    bool Push(const T& item);
    bool  Pop(T &item);
    void ClearStack(void);
    T Peek(void) const;
    int StackEmpty(void) const;
    int StackFull(void) const;
};

template <class T>
Stack<T>::Stack() {
	memset(stacklist, T(), sizeof(T)*MaxStackSize);
	m_top = -1;
}

template <class T>
bool Stack<T>::Push(const T& item) {
    if (m_top >= MaxStackSize) {
		stacklist[++m_top] = item;
		return true;
    }
	return false;
}

template <class T>
bool Stack<T>::Pop(T& item) {
	if (m_top >= 0) {
		item = stacklist[m_top--];
		return true;
	}
	return false;
}

template <class T>
void Stack<T>::ClearStack() {
	m_top = -1;
}

template <class T>
T Stack<T>::Peek() const {
	return stacklist[m_top];
}

template <class T>
int Stack<T>::StackEmpty() const {
	return (m_top == -1);
}

template <class T>
int Stack<T>::StackFull() const {
	return (m_top == MaxStackSize - 1);
}

bool match(string &buff) {
	Stack<char> stack;
	char ch1 = 0;

	for (auto ch : buff) {
		switch (ch) {
		case '(': case '[':
			stack.Push(ch);
			break;
		case ')':
			if (!stack.Pop(ch1)) {
				return false;
			}
			if (ch1 != '(') {
				return false;
			}
			break;
		case ']':
			if (!stack.Pop(ch1)) {
				return false;
			}
			if (ch1 != '[') {
				return false;
			}
			break;
		}
	}

	return true;
}


int main() {
	string buff;
	cin >> buff;
	if (match(buff)) {
		cout << "TRUE" << endl;
	}
	else {
		cout << "FALSE" << endl;
	}
    return 0;
}
