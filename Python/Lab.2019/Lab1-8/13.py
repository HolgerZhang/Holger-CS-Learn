"""
13. 从键盘输入两个时间点，格式 hh:mm:ss（时：分：秒），计算两个时间点
    相隔的秒数，并输出。
"""


def func(time1, time2):
    h1, m1, s1 = map(int, time1.split(":"))
    h2, m2, s2 = map(int, time2.split(":"))
    first = h1 * 3600 + m1 * 60 + s1
    second = h2 * 3600 + m2 * 60 + s2
    return abs(second - first)


if __name__ == "__main__":
    time1 = input("第一个时间点：")
    time2 = input("第二个时间点：")
    print("相隔的秒数：%d" % func(time1, time2))
