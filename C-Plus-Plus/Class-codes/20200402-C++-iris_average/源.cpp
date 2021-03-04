#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

int main() {
	ifstream data("iris.dat");
	if (!data) {
		cout << "File Not Found!" << endl;
		return 0;
	}
	ofstream result("result.dat");
	
	while (!data.eof()) {
		string buff;
		double sum = 0.0;
		for (int i = 0; i < 4; i++) {
			getline(data, buff, ',');
			istringstream is(buff);
			double num;
			is >> num;
			sum += num;
		}
		if (buff == "\n") {
			break;
		}
		getline(data, buff, '\n');
		result << sum / 4 << endl;
	}

	data.close();
	result.close();
	return 0;
}