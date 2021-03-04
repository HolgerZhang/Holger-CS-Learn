"""
46. 编写一个加密函数，实现对一个给定字符串中的字母转变为其后 n 个字符，
    如果遇到超过字母边界，则从最小字母继续计数，连续的数字字符作为一个
    整数扩大 n 倍之后替换到对应位置，其中 n 默认为 5。再编写一个解密函数
    实现对上述加密字符串进行解密。编写测试程序，在测试程序中输入字符串，
    并输出加密和解密后的字符串。
"""
from string import ascii_lowercase as low
from string import ascii_uppercase as up
import re


def rep(m, n=5, decode=False):
    # 数字替换函数
    if decode:
        return str(int(m.group(0)) // n)
    return str(int(m.group(0)) * n)


def str_encrypt(s, n=5):
    # 加密函数
    tran = str.maketrans(low + up, low[n:]+low[:n]+up[n:]+up[:n])
    s = s.translate(tran)
    pattern = re.compile(r"\d+")
    return pattern.sub(lambda m: rep(m, n), s)


def str_decode(s, n=5):
    # 解密函数
    tran = str.maketrans(low[n:]+low[:n]+up[n:]+up[:n], low + up)
    s = s.translate(tran)
    pattern = re.compile(r"\d+")
    return pattern.sub(lambda m: rep(m, n, decode=True), s)


if __name__ == "__main__":
    s = input("请输入一个字符串:")
    n = int(input("n = "))
    print("加密后:", str_encrypt(s, n))
    print("解密后:", str_decode(str_encrypt(s, n)))
