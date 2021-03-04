"""
57. 英语语法中，动词的第三人称单数形式规则简要概括（不完全）如下：
    a) 如果动词以 y 字母结尾，则去掉 y 并加上 ies。
    b) 如果动词以 o， ch，s， sh， x， z 字母结尾，则加上 es。
    c) 默认直接在动词最后加上字母 s。
    现在请你写一个程序，对于任意给定的一个动词，返回其第三人称单数形式。
"""
import re


def func(s):
    y_to_ies = re.sub('y$', 'ies', s)
    if y_to_ies != s:
        return y_to_ies

    pattern = re.compile('^[a-zA-Z]*[ozxs(sh)(ch)]$')
    append_es = pattern.match(s)
    if append_es:
        return ''.join([append_es.group(0), 'es'])

    return ''.join([s, 's'])


if __name__ == "__main__":
    word = input('请输入一个动词：')
    print('第三人称单数：', func(word))
