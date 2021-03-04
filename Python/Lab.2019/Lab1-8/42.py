"""
42. 编写一个函数，计算一个整数的所有因子之和，其中因子不包括整数本身，
    并编写测试程序，在测试程序中输入整数和输出整数的所有因子之和。
"""


def func(n):
    return sum([i for i in range(1, n) if n%i == 0])


if __name__ == "__main__":
    n = int(input('请输入一个整数：'))
    print('所有因子之和为：%d' % func(n))
