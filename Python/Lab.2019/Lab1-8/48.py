"""
48. 编写一个函数，统计一个给定的英文语句中，某个指定位置的字符在字符串
    中出现的次数，统计时不区分字母的大小写，默认字符位置为 0。编写测试
    程序，在测试程序中输入英文语句，指定要查找的字符位置，并输出该字符
    在语句中出现的次数。
"""


def func(st, n=0):
    if n not in range(len(st)):
        return None
    st = st.lower()
    char = st[n]
    return st.count(char)


if __name__ == "__main__":
    st = input('输入英文语句：')
    n = int(input('位置：'))
    print('位置%d的字符在英文语句中出现的次数为%d'%(n,func(st,n)))
