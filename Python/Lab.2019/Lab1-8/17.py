"""
17. 已知一个整数列表，判断列表内容是否为回文，即无论正序还是倒序列表的内容相同
"""


def judgement(renum):
    return renum == renum[::-1]


if __name__ == "__main__":
    print(judgement(eval(input("请输入一个列表："))))
