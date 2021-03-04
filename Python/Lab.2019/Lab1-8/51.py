"""
51. 编写一个函数实现选择排序。从键盘依次输入 10 个字母（如果有大小写，需
    要区分），按照字母的 ASCII 码值分别进行从小到大、从大到小的排序，并输
    出排序的结果。
"""


def choosesort(lst, key=lambda x: x, reverse=False):
    lst = lst[:]
    for i in range(len(lst)-1):
        m = i  # 假设i位置最大/小
        for j in range(i+1, len(lst)):
            # 选出未排序区域的最大/最小元素的下标
            if not reverse:
                if key(lst[j]) < key(lst[m]):
                    m = j
            else:
                if key(lst[j]) > key(lst[m]):
                    m = j
        if m != i:  # 最大/小不是i，交换
            lst[i], lst[m] = lst[m], lst[i]
    return lst


if __name__ == "__main__":
    aim = [input('Please input the character%d:' % i) for i in range(1, 11)]
    print('From small to large:', end='')
    for i in choosesort(aim, key=lambda x: ord(x)):
        print(i, end=' ')
    print()
    print('From large to small:', end='')
    for i in choosesort(aim, key=lambda x: ord(x), reverse=True):
        print(i, end=' ')
    print()
