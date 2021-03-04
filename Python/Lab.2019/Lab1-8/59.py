"""
59. 编写一个函数，将一个 a 进制的数转换成一个 b 进制的数，其中 a 和 b 都
    在[2, 16]之间。该函数有 3 个参数，前两个参数分别是 a 和 b，第三个参数
    是一个字符串，表示a进制的数。如果a和b 不在给定范围之内，返回None，
    否则返回对应的 b 进制数。
"""


def func(a, b, s):
    if a not in range(2, 17) and b not in range(2, 17):
        return None

    low = {'A': 10, 'B': 11, 'C': 12, 'D': 13, 'E': 14, 'F': 15}
    d = 0  # 十进制数
    step = len(s)
    for i in list(s):
        step -= 1
        d += (int(i) if ord(i) in range(48, 58) else low[i])*(a**step)

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


if __name__ == "__main__":
    a = int(input('a='))
    b = int(input('b='))
    s = input("a进制数为：")
    print("b进制数为：%s" % func(a, b, s))
