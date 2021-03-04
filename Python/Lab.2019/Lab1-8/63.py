"""
63. 现在 8 名体检人员的体重信息如下 (65.5, 70.2, 100.5, 45.5, 88.8,
    55.5, 73.5, 67.8)，请编写程序计算出方差。
"""


def Variance(tup):
    aver = sum(tup) / len(tup)
    res = 0
    for i in range(len(tup)):
        res += (tup[i] - aver) ** 2
    res /= len(tup)
    return res


if __name__ == "__main__":
    Weight = (65.5, 70.2, 100.5, 45.5, 88.8, 55.5, 73.5, 67.8)
    print("The variance of their weights is %f" % Variance(Weight))
