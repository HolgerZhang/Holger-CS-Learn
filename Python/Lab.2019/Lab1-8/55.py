"""
55. 给定字符串，将其中的单词倒序输出。
"""


def ReverseSentense(s):
    return ' '.join(reversed(s.split()))


if __name__ == "__main__":
    s = input('请输入一个字符串：')
    print('单词倒序输出为：', ReverseSentense(s))
