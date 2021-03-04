"""
47. 编写一个函数，将给定英文语句中的单词倒序。编写测试程序，从键盘输入
    英文语句，并输出倒序后的英语字符串。
"""


def func(st):
    return ' '.join(reversed(st.split()))


if __name__ == "__main__":
    st = input('请输入一个英文语句：')
    print('倒叙：%s' % func(st))
