"""
14. 请编写一个程序，产生两个[10，50]之间的随机数，用这两个数构造一个复
    数，计算复数的模、辐角(要求转换成角度)，最后将复数、复数的模和辐角显
    示在屏幕上。要求每个占 7 列，保留 2 位小数，右对齐。
"""
import random
import math


def ComplexNumber():
    a = random.randint(10, 50)
    b = random.randint(10, 50)
    z = complex(a, b)
    return z, abs(z), math.atan(b/a) * 180 / math.pi


if __name__ == "__main__":
    print("复数：%7r，复数的模：%7.2f，辐角：%7.2f°" % ComplexNumber())
