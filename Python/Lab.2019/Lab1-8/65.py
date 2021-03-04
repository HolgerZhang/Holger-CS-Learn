"""
65. 从键盘上随机输入若干个大写英文字母，编写程序使用字典统计所输入的每
    个字母出现的次数。
"""


def CountChr(s):
    d = dict()
    for i in s:
        d[i] = d.get(i, 0) + 1
    return d


if __name__ == "__main__":
    print(CountChr(input("INPUT: ")))
