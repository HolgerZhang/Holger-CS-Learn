//��ģ��дһ��ͨ�õĿ��Զ������Ԫ�ص���ֵ���͵���������ĺ���
#include<iostream>
using namespace std;

/**
�������Ԫ�ص���ֵ���͵�����ԭ������ѡ������
ģ�����˵����
	T: ��ֵ���͵��������ͣ�����int��long��double�ȵ�
�β�˵����
	arr: �����׵�ַ
	size: �����С
	reverse: �Ƿ�Ӵ�С����Ĭ�ϴ�С����false��
����ֵ˵����
	������������׵�ַ
*/
template <typename T>
T* sort(T* const arr, int size, bool reverse = false) {
	for (T* forwardPtr = arr; forwardPtr < arr+size-1; forwardPtr++) {
		T* assume = forwardPtr;		//����forePtrָ��Ԫ�����/С
		for (T* backPtr = forwardPtr+1; backPtr < arr+size; backPtr++) {
			//�ҳ�ָ��δ������������/СԪ�ص�ָ�룬��assume����
			if (reverse ? (*backPtr > *assume) : (*backPtr < *assume)) {
				assume = backPtr;
			}
		}
		if (assume != forwardPtr) {	
			//���/С����forePtrָ���Ԫ�أ�������ָ��ָ�������
			T temp = *assume;
			*assume = *forwardPtr;
			*forwardPtr = temp;
		}
	}
	return arr;
}

/**
��������Ԫ�ص���ֵ���͵�����
ģ�����˵����
	T: ��ֵ���͵��������ͣ�����int��long��double�ȵ�
�β�˵����
	arr: �����׵�ַ
	size: �����С
����ֵ˵����
	�޷���ֵ
*/
template <typename T>
void show(const T* arr, int size) {
	const T* end = arr + size;
	for (; arr < end; arr++) {
		cout << *arr << '\t';
	}
	cout << endl;
}

int main() {
	int arr[5] = { 10,4,9,2,1 };								//int����
	show(sort(arr, 5), 5);
	show(sort(arr, 5, true), 5);
	double darr[7] = { 10.3,-4.4,8.9,0.2,10.0,5.5,-6.7 };	//double����
	show(sort(darr, 7), 7);
	show(sort(darr, 7, true), 7);
	char carr[8] = { 'c','f','q','z','.','E','B','(' };		//char����
	show(sort(carr, 8), 7);
	show(sort(carr, 8, true), 8);
	return 0;
}