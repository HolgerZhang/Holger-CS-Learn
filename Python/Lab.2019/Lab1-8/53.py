"""
53. 写一个程序，用户输入一个字符串 s，返回一个由 s 的前 2 个字符和后 2 个
    字符组成的新字符串。如果 s 的长度小于 2，则返回空字符串。
"""


def func(s):
    if len(s) < 2:
        return ''
    return ''.join([s[0], s[1], s[-2], s[-1]])


if __name__ == "__main__":
    s = input('请输入一个字符串：')
    print('新字符串为：', func(s))
