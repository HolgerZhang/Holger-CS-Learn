"""
25. 小明带着 N 元钱去买酱油。酱油 15 块钱一瓶，商家进行促销，每买 3 瓶送
    1 瓶，或者每买 5 瓶送 2 瓶。请问小明最多可以得到多少瓶酱油。N 的数值
    由用户输入，并且一定是整数。
"""


def botton(n):
    five, three = 0, 0
    if n >= 75:
        five = n // 75
        n %= 75
    if n >= 45:
        three = n // 45
        n %= 45
    one = n // 15
    return five * 7 + three * 4 + one


if __name__ == "__main__":
    N = int(input('小明带了几元钱?'))
    print('小明最多能可以得到%d瓶酱油' % botton(N))


