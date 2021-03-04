//文件流
#include<iostream>
#include<fstream>
using namespace std;

int main() {
	ofstream ofile("d:\\input.txt");
	ifstream inFile("d:\\output.txt");	//物理路径用\\, 虚拟路径用/
	if (!inFile) {
		cout << "打开文件失败";
		return 0;
	}
	char ch;
	while (!inFile.eof()) {
		ch = inFile.get();
		ch = ch ^ 0x80;	//简单的加密：a^b=c, c^b=a
		ofile << ch;
	}
	inFile.close();
	ofile.close();
	return 0;
}