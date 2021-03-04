//用模板写一个通用的可以对任意个元素的数值类型的数组排序的函数
#include<iostream>
using namespace std;

/**
对任意个元素的数值类型的数组原地排序（选择排序）
模板参数说明：
	T: 数值类型的数据类型，例如int、long、double等等
形参说明：
	arr: 数组首地址
	size: 数组大小
	reverse: 是否从大到小排序，默认从小到大（false）
返回值说明：
	排序后该数组的首地址
*/
template <typename T>
T* sort(T* const arr, int size, bool reverse = false) {
	for (T* forwardPtr = arr; forwardPtr < arr+size-1; forwardPtr++) {
		T* assume = forwardPtr;		//假设forePtr指向元素最大/小
		for (T* backPtr = forwardPtr+1; backPtr < arr+size; backPtr++) {
			//找出指向未排序区域的最大/小元素的指针，用assume保存
			if (reverse ? (*backPtr > *assume) : (*backPtr < *assume)) {
				assume = backPtr;
			}
		}
		if (assume != forwardPtr) {	
			//最大/小不是forePtr指向的元素，交换两指针指向的内容
			T temp = *assume;
			*assume = *forwardPtr;
			*forwardPtr = temp;
		}
	}
	return arr;
}

/**
输出任意个元素的数值类型的数组
模板参数说明：
	T: 数值类型的数据类型，例如int、long、double等等
形参说明：
	arr: 数组首地址
	size: 数组大小
返回值说明：
	无返回值
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
	int arr[5] = { 10,4,9,2,1 };								//int数组
	show(sort(arr, 5), 5);
	show(sort(arr, 5, true), 5);
	double darr[7] = { 10.3,-4.4,8.9,0.2,10.0,5.5,-6.7 };	//double数组
	show(sort(darr, 7), 7);
	show(sort(darr, 7, true), 7);
	char carr[8] = { 'c','f','q','z','.','E','B','(' };		//char数组
	show(sort(carr, 8), 7);
	show(sort(carr, 8, true), 8);
	return 0;
}