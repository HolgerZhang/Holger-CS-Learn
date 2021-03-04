"""
44. 反素数指一个素数将其逆向拼写后也是一个素数的非回文数。例如：17 和 71
    都是素数且都不是回文数，所以 17 和 71 都是反素数。请编写一个函数判断
    一个数是否是反素数？并编写测试程序找出前 30 个反素数输出到屏幕上，
    要求每行输出 8 个数，每个数占 5 列，右对齐。
"""


def isprime(n):
    if n >= 2:
        for i in range(2, n):
            if n % i == 0:
                return False
        return True
    return False


def isrevprime(n):
    rev = int(''.join(reversed(str(n))))
    return isprime(n) and isprime(rev) if n != rev else False


if __name__ == "__main__":
    i, j = 2, 0
    while j < 30:
        if isrevprime(i):
            print("%5d" % i, end="")
            j += 1
            if j % 8 == 0:
                print()
        i += 1
    print()
