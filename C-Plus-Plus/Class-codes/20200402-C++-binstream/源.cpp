//�ö����Ʒ�ʽ���ļ������ж�д����
#include<iostream>
#include<fstream>
using namespace std;

int main() {
	ifstream inFile("d:\\input.txt", ios::binary | ios::in);
	if (!inFile) {
		cout << "File Not Found!" << endl;
		return 0;
	}
	ofstream outFile("d:\\output.txt", ios::binary | ios::out);
	char ch;
	while (!inFile.eof()) {
		inFile.read(&ch, sizeof(ch));
		ch ^= 0x80;
		outFile.write(&ch, sizeof(ch));
	}
	inFile.close();
	outFile.close();
	return 0;
}