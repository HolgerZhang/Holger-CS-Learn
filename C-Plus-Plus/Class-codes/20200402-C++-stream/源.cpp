//�ļ���
#include<iostream>
#include<fstream>
using namespace std;

int main() {
	ofstream ofile("d:\\input.txt");
	ifstream inFile("d:\\output.txt");	//����·����\\, ����·����/
	if (!inFile) {
		cout << "���ļ�ʧ��";
		return 0;
	}
	char ch;
	while (!inFile.eof()) {
		ch = inFile.get();
		ch = ch ^ 0x80;	//�򵥵ļ��ܣ�a^b=c, c^b=a
		ofile << ch;
	}
	inFile.close();
	ofile.close();
	return 0;
}