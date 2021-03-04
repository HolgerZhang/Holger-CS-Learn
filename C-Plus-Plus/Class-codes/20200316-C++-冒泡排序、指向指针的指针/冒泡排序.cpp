//ð�����򣺶��ַ�������
#include<iostream>
#include<cstring>
using namespace std;

void mySort(char**, int, int(*)(const char*, const char*) = &strcmp);
int lengthcmp(const char*, const char*);

int main()
{
	char* months[12] = {		//������ָ������
		"January",	"February",	"March",		"April",		"May",		"June",
		"July",		"August",	"September",	"October",	"November",	"December"
	};

	mySort(months, 12);	//Ĭ���ֵ�������
	for (int i = 0; i < 12; i++) {
		cout.width(16); cout << left;
		cout << months[i];
		if ((i + 1) % 6 == 0) {
			cout << endl;
		}
	}
	cout << endl;

	mySort(months, 12, &lengthcmp);	//�����ַ����ĳ�������
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

//�����ַ����ĳ������Ƚϴ�С
int lengthcmp(const char* str1, const char* str2) {
	return (strlen(str1) - strlen(str2));
}

//���� ����ָ�� �� ָ��ָ���ָ�� ����
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
