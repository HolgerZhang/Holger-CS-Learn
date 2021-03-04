"""
7.  从键盘输入一个 3 位整数，请编写程序计算三位整数的各位数字之和，并输
    出到屏幕上，要求输出占 4 列，右对齐。
"""


def func(a):
    return sum(map(int, str(a)))


if __name__ == "__main__":
    a = int(input("输入一个 3 位整数:"))
    print("各位数字之和为%4d" % func(a))
