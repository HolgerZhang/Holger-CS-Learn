"""
61. 请利用正则表达式写一个简单的拼写检查程序。实现以下功能：
    a) 两个或两个以上的空格出现时将其压缩为一个。
    b) 在标点符号后加上一个空格，如果这个标点符合之后还有字母。
"""
import re


def SpellCheck(s):
    return ' '.join(re.findall('\w+[,.!?:;]|\w+', s))


if __name__ == "__main__":
    print('正确拼写：%s' % SpellCheck(input('请输入一个字符串：')))
