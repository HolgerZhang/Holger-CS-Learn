"""
3. 编写程序让用户输入自己姓名，输出该姓名字符串的长度。
"""


def count_len(a):
    return len(a)


if __name__ == "__main__":
    a = input("请输入你的姓名:")
    print("你的姓名长度为 %d" % count_len(a))