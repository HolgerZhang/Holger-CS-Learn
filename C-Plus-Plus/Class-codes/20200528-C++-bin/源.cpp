#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

string bin(int num) {
    ostringstream out;
    while (num != 0) {
        out << (num % 2);
        num /= 2;
    }
    string res = out.str();
    if (res.length() == 0) { res += "0"; }
    reverse(res.begin(), res.end());
    return res;
}

void bin_recursion(int num) {
    if (num == 0) { return; }
    bin_recursion(num / 2);
    cout << (num % 2);
}

void bin_bitwise(int num) {
	int flag = 0;
    for (int i = 8 * sizeof(int) - 1; i >= 0; --i) {
		int bit = num >> i & 0x01;
		if (flag == 0 && bit != 0) {
			flag = 1;
		}
		if (flag) {
			cout << bit;
		}
    }
}

int main() {
    int num = 89;
    bin_bitwise(num);
    return 0;
}
