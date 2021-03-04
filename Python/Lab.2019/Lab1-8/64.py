"""
64. 使用元组编写程序，模拟评委打分的过程。评委打分标准：去掉 1 个最高分
    和 1 个最低分，计算平均分。
"""


def func(tp):
    return sum(sorted(tp)[1:-1])/(len(tp)-2)


if __name__ == "__main__":
    print(func((1,2,5,4,6,9,10,2,8)))


