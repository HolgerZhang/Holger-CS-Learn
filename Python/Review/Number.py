"""
    数字有关固定解法
    index:
        pre: 求一个整数的各位数、位数、逆序数、向上取整、二进制形式中有多少个1
        ## 判断质数（素数）： isprime(n)
        ## 判断反素数: isrevprime(n)
        ## 判断梅森素数: ismeisen(n)
         # Fibonacci数列第n项: fib(n)
        ## 判断互质: func1_2018_2(m, n)
        ## 计算逆序数: func2_2018_2(lst)
        ## 辗转相除法: divi(a, b)
        ## 任意进制（2-16）的转换: tranint(a, b, s)

"""
import math


# 求一个整数的各位数、位数、逆序数:
# >>> each = [int(i) for i in str(number)]
# >>> bit = len(each)
# >>> reverse_number = int(''.join([str(i) for i in reversed(each)]))

# math.ceil(4.12)  向上取整

# bin(x).count('1')  给定一个正整数x，计算并返回x的二进制形式中有多少个1  (2019-1)


def isprime(n):
    """
    ## 判断质数（素数）
    :return: bool
    """
    if n >= 2:
        for i in range(2, n):
            if n % i == 0:
                return False
        return True
    return False


def isrevprime(n):
    """
    ## 判断反素数
    :return: bool
    """
    if isprime(n):
        revlst = list(str(n))
        revlst.reverse()
        rev = int(''.join(revlst))
        if rev != n:
            if isprime(rev):
                return True
    else:
        return False


def ismeisen(n):
    """
    ## 判断梅森素数
    :return: int
    """
    if isprime(n):
        for p in range(1, n):
            if n == 2 ** p - 1:
                return p
    return -1


def fib(n):
    # Fibonacci数列第n项
    if n == 0:
        return 1
    if n == 1:
        return 1
    else:
        return fib(n - 1) + fib(n - 2)


def func1_2018_2(m, n):
    """
    2018-2
    ## 判断互质
    1.	给定整数m和n，如果m和n都大于1，则判定m和n是否互质，并返回判定结果。
    :param m, n: int 大小关系未知 如果m和n中任何一个小于或等于1，则返回None，否则判定两数是否互质。
    :return: bool 如果m和n互质，则返回布尔值True，否则返回布尔值False。
    """
    if m <= 1 or n <= 1:
        return None
    for i in range(2, min(m, n) + 1):
        if m % i == 0 and n % i == 0:
            return False
    return True


if __name__ == "__main__":
    """ 测试用例 """
    print(func1_2018_2(2, 3))  # True
    print(func1_2018_2(-2, 2))  # None
    print(func1_2018_2(3, 6))  # False


def func2_2018_2(lst):
    """
    2018-2
    ## 计算逆序数
    2.	一个整数列表L=[a1, a2, …, an]中，如果一对数(ai, aj)满足ai>aj且i<j，
        那么这对数就称为一个逆序，列表L中逆序的数量称为逆序数。求一个整数列表L的逆序数。
    :return: int 如果L为空或者L中只有一个元素，返回0，否则返回L的逆序数。
    """
    lst = lst[:]
    if len(lst) <= 1:
        return 0
    else:
        a = 0
        for i in range(len(lst) - 1):
            for j in range(i + 1, len(lst)):
                if lst[i] > lst[j]:
                    a += 1
        return a


if __name__ == "__main__":
    """ 测试用例 """
    print(func2_2018_2([4, 3, 2, 1]))  # 6
    print(func2_2018_2([4, 1, 2, 3]))  # 3


def divi(a, b):
    """
    ## 辗转相除法
    :param a, b: int
    :return: 最大公约数
    ## math.gcd(a, b)  最大公约数
    ### 另：最小公倍数
        两个数的乘积等于这两个数的最大公约数与最小公倍数的积
        故 最小公倍数 = a * b / math.gcd(a, b)
    """
    if b == 0:
        print(a)
    else:
        divi(b, a % b)


def tranint(a, b, s):
    """
    ## 任意进制（2-16）的转换
    （除k取余法：余数倒排，到商为零结束）
    将一个a进制的数转换成一个b进制的数，其中a和b都在[2, 16]之间。
    :param a, b: int 进制数
    :param s: str a进制的数（A-F表示10-15）
    :return: srt b进制的数
    """
    if a not in range(2, 17) and b not in range(2, 17):
        return None

    low = {'A': 10, 'B': 11, 'C': 12, 'D': 13, 'E': 14, 'F': 15}
    d = 0  # 十进制数
    step = len(s)
    for i in list(s):
        step -= 1
        d += (int(i) if ord(i) in range(48, 58) else low[i]) * (a ** step)

    mod = []
    plus = {10: 'A', 11: 'B', 12: 'C', 13: 'D', 14: 'E', 15: 'F'}
    while d != 0:
        modnum = d % b
        if modnum < 10:
            mod.append(str(modnum))
        else:
            mod.append(plus[modnum])
        d //= b

    return ''.join(reversed(mod))
