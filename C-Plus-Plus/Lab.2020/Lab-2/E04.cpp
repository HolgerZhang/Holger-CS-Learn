/**
 * @file    E04.cpp
 * @create  2020/03/07
 * @encoding GBK
 * @author  Holger
 * @description
 *  公元前5世纪，我国数学家张丘建在《算经》中提出百钱百鸡问题：
 *  鸡翁一值钱五，鸡母一值钱三，鸡雏三值钱一，百钱买百鸡，问鸡翁、母、雏各几何？
 */
#include<iostream>
using namespace std;

/**百鸡百钱问题：
 * 设公鸡买x只，母鸡买y只，则小鸡买(100-x-y)只
 * 其中100钱最多买20只公鸡，33只母鸡
 * 100钱可以列式：5x+3y+(100-x-y)/3=100
 * 整理得：7x+4y=100（*），即 y=(100-7x)/4
 * 令x从0取到20，计算y并取整，如果满足（*）式即为所求
 */

int main()
{
	int cock, hen, chick;	//公鸡，母鸡，小鸡的数量
	//其中100钱最多买20只公鸡，令公鸡数量从0取到20
	for (cock = 0; cock <= 20; ++cock) {
		hen = (100 - 7 * cock) / 4;		//计算母鸡
		if (7 * cock + 4 * hen == 100 && hen >= 0 && hen <=33) {
			//母鸡只能买0到33只，如果满足（*）式即为所求
			chick = 100 - cock - hen;	//计算小鸡
			cout << "公鸡" << cock << "只，"
				 << "母鸡" << hen << "只，"
				 << "小鸡" << chick << "只。" << endl;
		}
	}
	return 0;
}