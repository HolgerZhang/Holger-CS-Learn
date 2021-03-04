"""
38. 提示用户输入一个整数 n,然后输出 [1,n) 之间所有的素数。
"""


def isPrime(n):
    if n >= 2:
        for i in range(2, n):
            if n % i == 0:
                return False
        return True
    return False


def prime_list(n):
    return [i for i in range(2,n) if isPrime(i)]


if __name__ == "__main__":
    print(*prime_list(int(input("n = "))), sep=', ')
