"""
70. 通过[0,500]范围内随机数发生的方法分别创建两个整数数据的集合，要求每
    个集合中数据的个数分别要超过 200 个。在此基础上实现：
    a)  求出两个集合中不相同的数据，并进行显示。要求每行显示 10 条，每个
        数占 5 列，右对齐；
    b)  求出两个集合中相同的数据，并进行显示。要求每行显示 10 条，每个数
        占 5 列，右对齐；
"""
import random


def MakeSets():
    s = set()
    while len(s) <= 200:
        s.add(random.randint(0, 500))
    return s


def Display(s):
    j = 0
    for i in s:
        print("%5d" % i, end='')
        j += 1
        if j % 10 == 0:
            print()
    print()


if __name__ == "__main__":
    A = MakeSets()
    B = MakeSets()
    print('set A:')
    Display(A)
    print('set B:')
    Display(B)
    print('Difference:')
    Display(A ^ B)
    print('Same:')
    Display(A & B)
