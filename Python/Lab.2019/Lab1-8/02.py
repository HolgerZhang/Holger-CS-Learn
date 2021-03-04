"""
2. 从键盘输入四个整数，并输出其中最大的数。
"""


def maxnum(n1, n2, n3, n4):
    return max(n1, n2, n3, n4)


if __name__ == "__main__":
    n1, n2, n3, n4 = map(int, input("请输入四个正整数：").split())
    print("最大值为：%d" % maxnum(n1, n2, n3, n4))
