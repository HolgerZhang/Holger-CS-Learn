class CA {
private:
	int m_x;
	friend int main();
public:

};

int main() {
	CA a1;
	a1.m_x = 1;
	return 0;
}