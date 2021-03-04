"""
8.  编写一个程序，提示用户输入三角形的三个顶点(x1，y1)、（x2，y2）、
    （x3，y3），然后计算三角形面积，这里假定输入的三个点能构成三角形。
    将面积输出到屏幕，要求输出占 7 列，保留 2 位小数，左对齐。
"""


def func(x1, y1, x2, y2, x3, y3):
    s_len = lambda XA, YA, XB, YB: ((XA - XB) ** 2 + (YA - YB) ** 2) ** 0.5
    side1 = s_len(x1, y1, x2, y2)
    side2 = s_len(x1, y1, x3, y3)
    side3 = s_len(x2, y2, x3, y3)
    p = (side1 + side2 + side3) / 2
    area = (p * (p - side1) * (p - side2) * (p - side3)) ** 0.5
    return area


if __name__ == "__main__":
    x1, y1 = map(int, input("请输入第一个点的坐标：").split())
    x2, y2 = map(int, input("请输入第二个点的坐标：").split())
    x3, y3 = map(int, input("请输入第三个点的坐标：").split())
    print("三角形面积为%-7.2f。" % func(x1, y1, x2, y2, x3, y3))
