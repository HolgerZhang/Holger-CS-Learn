""" 教材课后习题 """
import random
import re


def func1(num):  # 1-10 取一个3位以上数字的百位以上数字
    return num // 100  # 整除


def func2(y):  # 3-2 判断闰年: 能被400整除 或者能被4整除但不能被100整除
    if y % 400 == 0 or y % 4 == 0 and y % 100 != 0:
        return True  # or的优先级比and高
    else:
        return False


def func3():  # 3-4 生成50个随机数组成的列表，并删除奇数
    lst = [random.randint(1, 100) for i in range(50)]
    for index in range(len(lst) - 1, -1, -1):  # 倒序删除
        if lst[index] % 2 != 0: lst.pop(index)
    return lst


def func4():  # 3-5 生成50个随机数组成的列表，偶数下标的元素降序排列
    lst = [random.randint(1, 100) for i in range(20)]
    lst[::2] = sorted(lst[::2], reverse=True)  # 切片
    return lst


def func5(n):  # 3-6 因式分解：输出形如“60=2*2*3*5”的字符串
    if 0 <= n <= 1: return str(n) + '=' + str(n)
    result = str(n) + '='
    lst = [];
    i = 2
    while i <= n:
        while n % i == 0:
            lst.append(str(i))
            n = n // i
        i += 1
    return result + '*'.join(lst)


def func6(maxnum):  # 3-8 输出所有由1，2，3，4组成的素数，且每个数字只用一次。
    def isprime(n):
        # 5-2 判断素数
        if n >= 2:
            for i in range(2, int(n ** 0.5) + 1):
                if n % i == 0: return False
            return True
        return False

    from itertools import permutations as perm
    ori = list(map(str, range(1, maxnum + 1)))
    lst = []
    for i in map(int, ori):
        lst.extend([n for n in map(lambda x: int(''.join(x)), perm(ori, i)) if isprime(n)])
    lst.sort()
    return lst


def func7(s):  # 5-3 统计字符串中大写字母、小写字母、数字、其他字符的个数
    from string import ascii_uppercase as up  # 大写字母
    from string import ascii_lowercase as low  # 小写字母
    from string import digits as dig  # 数字
    up_len, low_len, dig_len, other = 0, 0, 0, 0
    for x in s:
        if x in up:
            up_len += 1
        elif x in low:
            low_len += 1
        elif x in dig:
            dig_len += 1
        else:
            other += 1
    return up_len, low_len, dig_len, other


def func8(*args: int):  # 5-9 接受任意个整数,返回最大值和总和
    if len(args) == 0: return
    return max(args), sum(args)


def func9():  # 2-10 前十个数升序，后十个数降序
    lst = [random.randint(1, 100) for i in range(20)]
    lst[:10] = sorted(lst[:10])
    lst[10:] = sorted(lst[10:], reverse=True)
    return lst


def func10(s):  # 4-1 单独的i改为I
    pattern = re.compile(r'\bi\b')
    return pattern.sub('I', s)


def func11(s):  # 4-2 单词中的I改为i
    pattern = re.compile(r'\b\w+I\w+\b')

    def rep(m):
        return re.sub(r'I', 'i', m.group(0))

    return pattern.sub(rep, s)


def func12(s):  # 4-3 删除重复的单词
    pattern = re.compile(r'\b\w+\b')
    flag = 0
    while True:
        find = pattern.search(s[flag:])  # 找
        if not find: break
        if s.count(find.group(0)) > 1:  # 如果重复，删
            s = s[:flag].strip() + " " + pattern.sub('', s[flag:], count=1).strip()
        flag += find.end(0)
    return s


def func13(s, n=3):  # 4-5 找出所有长度为n=3的单词
    return re.findall(r'\b\w{%d}\b' % n, s)


if __name__ == "__main__":
    print(func1(1456))
    print(func2(2014))
    print(func2(2016))
    print(func2(2000))
    print(func2(1900))
    print(func3())
    print(func4())
    print(func5(60))
    print(func5(10))
    print(func5(2))
    print(func5(1))
    print(func4())
    print(func6(4))
    print(func7("asdfghAS3sdg4#sdfa%&BFD#$%y76"))
    print(func8(1,2,5,6))
    print(func9())
    print(func10('so did i. i think so.'))
    print(func11('so dId I. ThIs is a desk.'))
    print(func12('This is is a a desk.'))
    print(func13('AB ABC ABCDF ABDCEF AASSDDFF ASD ZXC'))

"""
    运行结果：
    14
    False
    True
    True
    False
    [70, 66, 32, 36, 38, 52, 18, 2, 40, 48, 68, 4, 36, 20, 30, 76, 52, 90, 94, 36, 60, 86, 20, 4, 28, 6, 62, 82, 20, 94, 10]
    [94, 67, 93, 64, 81, 99, 49, 12, 35, 56, 13, 100, 13, 60, 8, 23, 4, 46, 1, 68]
    60=2*2*3*5
    10=2*5
    2=2
    1=1
    [98, 6, 98, 47, 88, 77, 85, 81, 81, 94, 74, 65, 73, 1, 68, 12, 40, 84, 27, 76]
    [2, 3, 13, 23, 31, 41, 43, 241, 421, 431, 1423, 2143, 2341, 4231]
    (5, 14, 4, 6)
    (6, 14)
    [6, 16, 20, 57, 58, 63, 63, 79, 83, 86, 95, 94, 82, 72, 67, 61, 43, 18, 8, 2]
    so did I. I think so.
    so did I. This is a desk.
    This is a desk.
    ['ABC', 'ASD', 'ZXC']
"""