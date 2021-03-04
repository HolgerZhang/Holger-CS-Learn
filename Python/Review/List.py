"""
    列表有关操作
    index:
        pre: 奇数位数字之和、倒序列表的两种方法、列表深拷贝、统计可迭代对象a中每个元素的数目
        ## 列表部分逆序: func7_2018_1(k, lst)
        ## 一维列表转成二维列表: func4_2018_2(lst)
        ## 去除列表中某一元素（原列表不变）: rmoneValue(lst,x)
        ## 列表去重（保持顺序）: rmRepeatValue(lst, key=lambda x:x)
         # 判断一个数字中是否包含某个数字: JudgeIfInNumber(testnum, number)
"""


# a.sort(key=lambda x:sum(list(map(int,list(str(x))))[-1::-2])) # 奇数位数字之和！！！

# # 倒序列表的两种方法
# >>> a_list = [3, 5, 7, 2, 0, 1]
# >>> print(a_list)  # result:[3, 5, 7, 2, 0, 1]
# >>> re_list = list(reversed(a_list))
# >>> print(re_list)  # result:[1, 0, 2, 7, 5, 3]
# >>> a_list.reverse()
# >>> print(a_list)  # result:[1, 0, 2, 7, 5, 3]

# lst = [] + lst  # 列表深拷贝

# # 统计可迭代对象a中每个元素的数目 -> dict
# >>> d = dict()
# >>> for i in a:
# ...    d[i] = d.get(i, 0) + 1


def func7_2018_1(k, lst):
    """
    2018-1
    ## 列表部分逆序
    7.将列表中前k个元素逆序。输出最后得到的列表。
      如果k大于列表长度，则将整个列表逆序。
      例如k=4，输入列表是[3,4,1,5,2]，那么返回列表是[5,1,4,3,2]。
    :param k:正整数
    :param lst:整数列表
    :return: list
    """
    if k <= len(lst):
        lst[:k] = reversed(lst[:k])
    else:
        lst.reverse()
    return lst

if __name__ == "__main__":
    """ 测试用例 """
    print(func7_2018_1(4, [3, 4, 1, 5, 2]))  # [5, 1, 4, 3, 2]
    print(func7_2018_1(5, [3, 4, 1, 5, 2]))  # [2, 5, 1, 4, 3]
    print(func7_2018_1(6, [3, 4, 1, 5, 2]))  # [2, 5, 1, 4, 3]
    print(func7_2018_1(2, [3, 4, 1, 5, 2]))  # [4, 3, 1, 5, 2]


def func4_2018_2(lst):
    """
    2018-2    4
    ## 一维列表转成二维列表
    Tip: 一维列表能保证长度是n*n(n>=1)
    """
    n = int(len(lst) ** 0.5)
    return [lst[0 + i * n:n + i * n] for i in range(n)]

if __name__ == "__main__":
    """ 测试用例 """
    print(func4_2018_2([1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6]))
    # [[1, 2, 3, 4], [5, 6, 7, 8], [9, 0, 1, 2], [3, 4, 5, 6]]


def rmoneValue(lst, x):
    """
    ## 去除列表中某一元素（原列表不变）
    :return: 新的列表
    """
    lst = lst[:]
    while x in lst: lst.remove(x)
    return lst

if __name__ == "__main__":
    """ 测试用例 """
    print(rmoneValue([1, 2, 3, 1, 2, 3], 1))  # [2, 3, 2, 3]


def rmRepeatValue(lst, key=lambda x: x):
    """
    ## 列表去重（保持顺序）
    不需保持顺序：return list(set(lst))
    :return: 去重后的列表
    """

    def doit(lst):
        """ 去重迭代器 """
        passed = set()
        for i in lst:
            value = key(i)
            if value not in passed:
                yield i
                passed.add(value)

    return list(doit(lst))

if __name__ == "__main__":
    """ 测试用例 """
    print(rmRepeatValue([1, 4, 2, 3, 1, 2, 3, 3, 4, 1], ))  # [1, 4, 2, 3]


def JudgeIfInNumber(testnum, number):
    # 判断一个数字中是否包含某个数字
    return str(testnum) in str(number)

if __name__ == "__main__":
    """ 测试用例 """
    print(JudgeIfInNumber(2, 230))  # True
    print(JudgeIfInNumber(1, 203))  # False
