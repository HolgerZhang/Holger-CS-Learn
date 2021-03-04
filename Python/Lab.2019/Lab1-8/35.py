"""
35. 输出一个乘法表。要求输入一个整数 n，输出 n*n 的乘法表，乘法表打印出
    来为下三角样式，格式工整。
"""


def func(n):
    multi = []
    for i in range(1, n + 1):
        line = []
        for j in range(1, i + 1):
            line.append(i * j)
        multi.append(line)
    return multi


def Display(lst):
    print('  ' * 5, end='')
    for k in range(1, len(lst[-1]) + 1):
        print('%-5d' % k, end='')
    print()
    for i in range(len(lst)):
        print('%-5d' % (i + 1), end='')
        for j in range(len(lst[i])):
            print('%-5d' % lst[i][j], end='')
        print()
    print()


if __name__ == "__main__":
    multilst = func(int(input('n=')))
    Display(multilst)
