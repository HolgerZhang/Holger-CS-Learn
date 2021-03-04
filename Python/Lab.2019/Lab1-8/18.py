"""
18. 已知一个整数列表，筛选出该列表中不同的质数，并求出该列表中有多少个
    质数可以表达为该列表中另外两个质数的和。
"""


def isPrime(n):
    if n >= 2:
        for i in range(2, n):
            if n % i == 0:
                return False
        return True
    return False


def find(total):
    # 筛选质数并排序
    prime = set()
    for n in total:
        if isPrime(n):
            prime.add(n)
    prime = sorted(list(prime))

    # 计数:多少个质数可以表达为该列表中另外两个质数的和
    s = 0
    for i in range(0, len(prime)-1):
        for j in range(i+1, len(prime)):
            if prime[i] + prime[j] in prime:
                s += 1
    return prime, s


if __name__ == "__main__":
    lst = eval(input("请输入一个列表："))
    prime, s = find(lst)
    print("列表中不同的质数有：", prime)
    print("其中有%d个质数可以表达为该列表中另外两个质数的和" % s)
