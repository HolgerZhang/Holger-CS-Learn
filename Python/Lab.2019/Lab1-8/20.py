"""
20. 现有列表[35, 46, 57, 13, 24, 35, 99, 68, 13, 79, 88, 46]，请编写程序将其
    中重复的元素去除，并按从小到大的顺序排列后输出。
"""


def func(alist):
    return sorted(list(set(alist)))


if __name__ == "__main__":
    print("去重后：",
          func([35, 46, 57, 13, 24, 35, 99, 68, 13, 79, 88, 46]))