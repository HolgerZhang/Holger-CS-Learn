"""
60. 一个字符串如果正读和反读都一样，那么它就是一个回文串。编写一个函数，
    判断一个字符串在下列规则下是否是回文串：1）忽略所有空格；2）忽略所
    有的句号、逗号、感叹号；3）不区分大小写。如果是回文串，返回 True，
    否则返回 False。
"""
import re


def isRevesedStr(s):
    a = ''.join(re.split('[,.!]+|\s+', s)).lower()
    return a == ''.join(reversed(a))


if __name__ == "__main__":
    s = input('请输入一个字符串：')
    print(isRevesedStr(s))
