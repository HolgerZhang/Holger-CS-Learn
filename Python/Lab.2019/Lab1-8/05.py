"""
5. 编写程序让用户输入两个平面上点的坐标，计算该两点间的距离。
"""
import math


def func(x1, y1, x2, y2):
    return math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)


if __name__ == "__main__":
    x1, y1 = map(int, input("请输入第一个点的坐标：").split())
    x2, y2 = map(int, input("请输入第一个点的坐标：").split())
    print("两点间的距离为：%f" % func(x1, y1, x2, y2))
