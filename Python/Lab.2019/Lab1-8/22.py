"""
22. 编写程序对一个 4*4 的矩阵进行随机赋值，然后对该矩阵进行转置，并输出
    转置后的结果。
"""
import random


def func(n):
    raw = [[random.randrange(1000) for j in range(n)]
                                   for i in range(n)]
    new = [[j[i] for j in raw] for i in range(n)]
    return raw, new


if __name__ == "__main__":
    print("原矩阵：%s\n转置后：%s" % func(4))
