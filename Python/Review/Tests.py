"""
    考试典型题整理
"""
import re


def func8_2018_1(v, lst):
    """
    2018-1
    8.给定一个数v和一个非负整数列表lst，去除其中“密度”小于v的整数，
      并将列表中剩余元素按从大到小的顺序排列。输出最后得到的列表。
      其中一个非负整数的“密度”定义为该整数的各位数字之和除以该整数的位数。
      例如123的密度为(1+2+3)/3=2，1234的密度为(1+2+3+4)/4=2.5。
    """
    for i in range(len(lst) - 1, -1, -1):
        d = sum(list(map(int, list(str(lst[i]))))) / len(str(lst[i]))
        if d < v:
            del lst[i]
    lst.sort(reverse=True)
    return lst

if __name__ == "__main__":
    """ 测试用例 """
    print(func8_2018_1(2, [111, 222, 333, 444, 1234, 1111]))  # [1234, 444, 333, 222]
    print(func8_2018_1(4, [111, 888, 0, 700, 1111, 55, 6]))  # [888, 55, 6]


def func7_2018_2(string1):
    """
    2018-2
    ## 统计重复字符
    7.	统计一个非空字符串中出现次数最多的字符及其出现次数。
        其中英文字母不区分大小写，全部统计为大写字母，如’a’和’A’在计数时进行合并为’A’。
        结果以包含字符和对应次数的列表形式进行返回。
        ! 数据中不存在并列最多的情况，该情况不需要考虑。
    :param string1: str 能保证目标字符串非空、且其中不存在出现次数并列最多的字符
    :return: list 包含字符和对应次数
    """
    string1 = string1.upper()
    sDict = dict()
    for x in list(string1):
        sDict[x] = list(string1).count(x)
    return list(max(list(sDict.items()), key=lambda x: x[1]))

if __name__ == "__main__":
    """ 测试用例 """
    print(func7_2018_2("1aA"))  # ['A', 2]


def func8_2018_2(string1):
    """
    2018-2
    ## 提取正整数
    8.	一个字符串中存在多个正整数，请提取出位数在[3,5]之间的所有正整数，构成一个列表，
        对此列表按照数字和平均值（各位数字的总和/位数）进行降序排序，并返回排序结果列表。
        数字和平均值就是各位数字的总和除以位数
        例如2345的数字和平均值=(2+3+4+5)/4=3.5，12的数字和平均值=(1+2)/2=1.5。
    :param string1: str 存在多个正整数的字符串
    :return: 以满足要求的列表形式进行返回。如原字符串中不存在满足条件的正整数，返回None
    """
    lst = [i for i in re.split('\D+', string1) if len(i) >= 3 and len(i) <= 5]
    lst.sort(key=lambda x: sum(list(map(int, list(x)))) / len(x), reverse=True)
    return list(map(int, lst))

if __name__ == "__main__":
    """ 测试用例 """
    print(func8_2018_2('123a4567 1'))  # [4567, 123]
    print(func8_2018_2('1234'))  # [1234]
    print(func8_2018_2('1234 sdjfh59832234 4958 sdj3 323n5555k5 m3 334'))  # [4958, 5555, 334, 323, 1234]


def kidgame(n, k):
    """
    (来自实验报告)
        有n个小朋友围成一圈玩游戏，小朋友从1至n编号，2号小朋友坐在1号
    小朋友的顺时针方向，3号小朋友坐在2号小朋友的顺时针方向，……，1号
    小朋友坐在n号小朋友的顺时针方向。
        从1号小朋友开始顺时针报数，接下来每个小朋友的报数是上一个小朋
    友报的数加1。若一个小朋友报的数为k的倍数，则该小朋友被淘汰出局，
    不再参加以后的报数。当游戏中只剩下一个小朋友时，该小朋友获胜。
        例如，当n=5, k=2 时：
        1 号小朋友报数1；2 号小朋友报数2 淘汰；
        3 号小朋友报数3；4 号小朋友报数4 淘汰；
        5 号小朋友报数5；1 号小朋友报数6 淘汰；
        3 号小朋友报数7；5 号小朋友报数8 淘汰；
        3 号小朋友获胜。
    让用户给定n 和k，请问最后获胜的小朋友编号为多少？
    """
    kids = list(range(1,n+1))
    num = 1
    if k == 1:
        return kids[-1]
    else:
        while len(kids) > 1:
            dellist =[]
            for i in range(len(kids)):
                if num % k == 0:
                    dellist.append(i)
                num += 1
            for j in dellist[::-1]:
                del kids[j]
                dellist.pop()
    return kids[0]
