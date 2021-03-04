"""
6.  产生一个随机 3 位正整数，并将该整数的数字首尾互换输出，
    例如：157 互换后为 751。
"""
import random


def func():
    num = random.randint(100, 999)
    eachnum = str(num)
    return num, int(''.join((eachnum[-1], eachnum[1:-1], eachnum[0])))


if __name__ == "__main__":
    print("三位整数是：%d\n首尾互换后为：%d" % func())