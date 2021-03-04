"""
39. 求Sn=a+aa+...+aa...a的值。其中 a 是一个数字。a 和 n 都是由键盘输入
"""


def func(a, n):
    s = 0
    sums = 0
    for i in range(1, n + 1):
        s += 10 ** (i - 1)
        sums += s
    return a * sums


if __name__ == "__main__":
    a = int(input('a='))
    n = int(input('n='))
    print(func(a, n))
