"""
16. 求无序整数列表的中位数。如列表元素为偶数个，则取列表升序排列时中间
    两数中数值较小的元素为中位数。
"""


def mid(numlist):
    numlist = numlist[:]
    numlist.sort()
    n = len(numlist) // 2
    return (numlist[n] + numlist[n - 1]) / 2 \
        if len(numlist) % 2 == 0 else numlist[n]


if __name__ == "__main__":
    numlist = eval(input("请输入一个列表："))
    print("中位数是：", mid(numlist))
