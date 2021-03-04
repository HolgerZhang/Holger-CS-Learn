"""
58. 编写一个函数，判断一个密码（用字符串表示）是否是好密码。一个好的密
    码满足：1）长度不小于 8；2）至少含有一个数字；3）至少含有一个小写字
    母；4）至少含有一个大写字母。如果密码是好密码，返回 True，否则返回False。
"""
import re


def GoodPassword(password):
    pattern = re.compile('^(?=.*[a-z])(?=.*[A-Z])(?=.*\d).{8,}$')  # positive lookahead assertion
    return pattern.match(password) is not None


if __name__ == "__main__":
    s = input('Password:')
    print(GoodPassword(s))
