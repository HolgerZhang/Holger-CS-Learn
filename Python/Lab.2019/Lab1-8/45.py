"""
45. 如果一个素数可以写成 2p-1 形式，其中 p 是一个正整数，那么该数就称作
    梅森素数。请编写一个函数判断一个素数是否是梅森素数，如果是，则返回
    p 的值，否则返回-1。并编写测试程序找出 1000 以内的所有梅森素数输出
    到屏幕上，要求输出格式如下：
    P(占 3 列右对齐) 2p-1 (占 4 列右对齐) # 此行不需要输出
"""


def isprime(n):
    if n >= 2:
        for i in range(2, n):
            if n % i == 0:
                return False
        return True
    return False


def ismeisen(n):
    if isprime(n):
        for p in range(1, n):
            if n == 2 ** p - 1:
                return p
    return -1


if __name__ == "__main__":
    for i in range(1000):
        p = ismeisen(i)
        if p != -1:
            print("%3d%4d" % (p,i))
    print()
