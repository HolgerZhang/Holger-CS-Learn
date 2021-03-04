"""
49. 编写一个递归函数，求解 Fibonacci 数列（兔子繁殖）问题的某项的值。编
    写测试程序，从键盘输入指定项，并输出 Fibonacci 数列指定项的值。
"""


def fib(n):
    if n == 0:
        return 1
    if n == 1:
        return 1
    else:
        return fib(n-1) + fib(n-2)


if __name__ == "__main__":
    n = int(input('Please input the term of Fibonacci(begin with 0):'))
    print('It is %d' % fib(n))