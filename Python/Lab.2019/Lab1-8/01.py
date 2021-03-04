"""
1. 从键盘输入两个正整数 a 和 b ，计算并输出 a/ b 的商和余数。
"""


def division(a, b):
    return a // b, a % b


if __name__ == "__main__":
    a, b = map(int, input("请输入两个正整数：").split())
    print("商为 %d ，余数为 %d" % division(a, b))
