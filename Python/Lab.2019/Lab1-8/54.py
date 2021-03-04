"""
54. 写一个程序处理用户输入的字符串，并按用户要求删除其中第 n 个字符，返
    回删除字符后的字符串。
"""


def DeleteN(s, n):
    n = n - 1
    return ''.join([s[:n], s[n+1:]])


if __name__ == "__main__":
    s = input('请输入一个字符串：')
    n = int(input('请输入一个整数(从1开始)：'))
    print('删除后为：', DeleteN(s, n))
