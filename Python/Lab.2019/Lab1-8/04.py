"""
4.  一只大象口渴了，要喝 20 升水才能解渴，但现在只有一个深 h 厘米，底面
    半径为 r 厘米的小圆桶(h 和 r 都是整数)。问大象至少要喝多少桶水才会解
    渴。编写程序输入半径和高度，输出需要的桶数（一定是整数）。
"""
import math


def func(h, r):
    V = math.pi * h * (r ** 2)
    N = math.ceil(20000 / V)
    return N


if __name__ == "__main__":
    h, r = map(int, input("请输入高度和半径：").split())
    print("需要的桶数为：%d" % func(h, r))
