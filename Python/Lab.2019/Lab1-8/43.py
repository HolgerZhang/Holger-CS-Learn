"""
43. 编写一个函数，将一个整数的各位数字对调，并编写测试程序，在测试函数
    中输入整数和输出新的整数。
"""


def revenum(n):
    # lst.reverse()
    return int(''.join(reversed(str(n))))


if __name__ == "__main__":
    n = int(input('请输入一个整数：'))
    print('翻转后为：%d' % revenum(n))