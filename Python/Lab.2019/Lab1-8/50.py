"""
50. 编写一个函数实现冒泡排序。从键盘输入依次输入 10 个整数，分别按照从小
    到大、从大到小进行排序，并分别输出排序后的结果
"""


def bubblesort(lst, key=lambda x: x, reverse=False):
    lst = lst[:]
    for i in range(len(lst)-1):
        while i >= 0:
            if not reverse:
                if key(lst[i]) > key(lst[i+1]):
                    lst[i], lst[i+1] = lst[i+1], lst[i]
            else:
                if key(lst[i]) < key(lst[i+1]):
                    lst[i], lst[i+1] = lst[i+1], lst[i]
            i -= 1
    return lst


if __name__ == "__main__":
    lst = [int(input('Please input the integer number%d:' % i))
           for i in range(1, 11)]
    print('From small to large:', end='')
    for i in bubblesort(lst):
        print(i, end=' ')
    print()
    print('From large to small:', end='')
    for i in bubblesort(lst, reverse=True):
        print(i, end=' ')
    print()
