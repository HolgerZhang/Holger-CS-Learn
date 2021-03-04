//输出30个不重复的1~50的随机数
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

int main()
{
	int nums[30] = { 0 };
	int flags[50] = { 0 };
	int i = 1;
	nums[0] = rand() % 50 + 1;
	flags[nums[0]-1] = 1;
	while (i < 30) {
		//srand((unsigned)time(NULL));
		int temp = rand() % 50 + 1;
		if (flags[temp-1] == 0) {
			nums[i] = temp;
			i++;
		}
	}
	for (int j = 0; j < 30; j++) {
		cout << nums[j] << '\t';
	}
	return 0;
}