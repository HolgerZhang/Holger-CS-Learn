"""
56. 统计一个字符串中所有字符出现的次数。
"""


def countstr(s):
    d = dict()
    for x in s:
        d[x] = d.get(x, 0) + 1
    return d


def Display(object):
    obj = sorted(list(object.items()), key=lambda x: (-x[1], x[0]))
    formatter = '\'{0[0]}\': {0[1]}'.format
    print(', '.join(map(formatter, obj)))


if __name__ == "__main__":
    s = input('请输入一个字符串：')
    Display(countstr(s))
