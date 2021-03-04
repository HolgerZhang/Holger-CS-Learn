"""
69. 小明想在学校中请一些同学一起做一项问卷调查，请编程帮助小明解决如下问题：
    a) 用户输入 N；
    b) 为了实验的客观性先用计算机生成N个1～1000之间的随机整数(N<=1000)；
    c) 对于其中重复的数字,只保留一个,将其余相同的数字去掉,不同的数对应着不同学生的学号；
    d) 然后再将这些数从小到大排序，按照排好的顺序去找同学做调查。输出排序的结果。
"""
import random


def FindStudents(N):
    return sorted({random.randint(1, 1000) for i in range(N)})


if __name__ == "__main__":
    N = int(input("N="))
    print(FindStudents(N))
