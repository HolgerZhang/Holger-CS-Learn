"""
30. 从键盘输入任意 3 个整数，按从小到大的顺序输出。
"""


def getorder(n1, n2, n3):
    return tuple(sorted((n1, n2, n3)))


if __name__ == "__main__":
    n1, n2, n3 = map(int, input("请输入三个整数：").split())
    print("%d < %d < %d" % getorder(n1, n2, n3))
