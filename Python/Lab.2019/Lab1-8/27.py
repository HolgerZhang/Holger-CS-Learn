"""
27. 从键盘分别输入 3 个 XOY 二维平面内某三角形的顶点坐标（6 个浮点数），
    在此基础上计算三角形的面积和周长。如果不能构成三角形需要提示错误信息。
"""


def func(x1, y1, x2, y2, x3, y3):
    sides = sorted([((x1 - x2) ** 2 + (y1 - y2) ** 2) ** 0.5,
                    ((x1 - x3) ** 2 + (y1 - y3) ** 2) ** 0.5,
                    ((x3 - x2) ** 2 + (y3 - y2) ** 2) ** 0.5])
    if sum(sides[:2]) > sides[2]:
        circle = sum(sides)
        p = circle / 2
        area = (p * (p - sides[0]) * (p - sides[1]) * (p - sides[2])) ** 0.5
        return area, circle
    else:
        return None


def Display(result):
    if result:
        print("三角形面积为%f,周长为%f" % result)
    else:
        print("不能构成三角形")


if __name__ == "__main__":
    x1, y1 = map(int, input("请输入第一个点的坐标：").split())
    x2, y2 = map(int, input("请输入第二个点的坐标：").split())
    x3, y3 = map(int, input("请输入第三个点的坐标：").split())
    Display(func(x1, y1, x2, y2, x3, y3))
