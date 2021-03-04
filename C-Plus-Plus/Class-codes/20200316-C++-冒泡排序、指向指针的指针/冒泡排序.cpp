//冒泡排序：对字符串排序
#include<iostream>
#include<cstring>
using namespace std;

void mySort(char**, int, int(*)(const char*, const char*) = &strcmp);
int lengthcmp(const char*, const char*);

int main()
{
	char* months[12] = {		//待排序指针数组
		"January",	"February",	"March",		"April",		"May",		"June",
		"July",		"August",	"September",	"October",	"November",	"December"
	};

	mySort(months, 12);	//默认字典序排序
	for (int i = 0; i < 12; i++) {
		cout.width(16); cout << left;
		cout << months[i];
		if ((i + 1) % 6 == 0) {
			cout << endl;
		}
	}
	cout << endl;

	mySort(months, 12, &lengthcmp);	//根据字符串的长度排序
	for (int i = 0; i < 12; i++) {
		cout.width(16); cout << left;
		cout << months[i];
		if ((i + 1) % 6 == 0) {
			cout << endl;
		}
	}
	cout << endl;
	return 0;
}

//根据字符串的长度来比较大小
int lengthcmp(const char* str1, const char* str2) {
	return (strlen(str1) - strlen(str2));
}

//利用 函数指针 和 指向指针的指针 排序
void mySort(char** arr, int size, int(*op)(const char* ,const char*))
{
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1 - i; j++) {
			if (op(arr[j], arr[j + 1]) > 0) {
				//swap
				char* temp;
				temp = *(arr + j);
				*(arr + j) = *(arr + j + 1);
				*(arr + j + 1) = temp;
			}
		}
	}
}
