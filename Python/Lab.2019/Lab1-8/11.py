"""
11. 请编写一个程序，产生一个在[5，20]之间的随机实数。假设该随机数是一个
    球的半径，请计算该球的体积。最后将球的半径和体积输出到屏幕上，要求
    每个值占 15 列，保留 3 位小数，右对齐。
"""
import random
import math


def func():
    r = random.uniform(5, 20)
    V = (4 * math.pi * r ** 3) / 3
    return r, V


if __name__ == "__main__":
    print("r=%15.3f\nV=%15.3f" % func())
