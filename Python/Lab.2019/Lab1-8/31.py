"""
31.从键盘输入一个十进制正整数，利用列表和除二取余法，计算出该数字的二进制值。
"""


def binarie(num):
    binarielist = []
    while num // 2 != 0:
        binarielist.append(num % 2)
        num //= 2
    binarielist.append(num % 2)
    binarielist.reverse()
    return int(''.join([str(i) for i in binarielist]))


if __name__ == "__main__":
    num = int(input("请输入一个十进制正整数："))
    print('该数字的二进制值为：', binarie(num))
