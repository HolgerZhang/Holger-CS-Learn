"""
29. 从键盘上输入一个不多于 5 位的正整数，编写程序实现如下要求
    （1）求出它是几位数；
    （2）分别输出每一位数字；
    （3）按逆序输出每位数字，例如原数为 321，应输出 123。
"""


def func(n):
    n = str(n)
    return len(n), list(n), ''.join(reversed(n))


if __name__ == "__main__":
    bit, lst, rev = func(int(input("请输入一个不多于5位的正整数：")))
    print("它是%d位数" % bit)
    print("每一位数字是：%s" % " ".join(lst))
    print("逆序输出每位数字:%s" % rev)

