#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    cout << "开始" << endl;
	try {
		cout << "进入try语句块." << endl;
		throw 200;
		cout << "不会被执行" << endl;
	}
	catch (int i) {
		cout << "捕获一个异常，它的值为：" << i << endl;
	}
	cout << "结束" << endl;
	return 0;
}
