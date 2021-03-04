"""
28. 从键盘输入两个浮点数 x1 和 y1 作为圆心坐标，从键盘输入一个浮点数 r 作
    为半径，这样就在 XOY 二维平面上唯一地确定了一个圆。再从键盘输入两
    个浮点数 x2 和 y2，编写程序以判断坐标点(x2, y2) 是在圆内还是在圆外
    （注在圆周上也是在圆内），并显示相应的判断结果。
"""


def func(x1, y1, r, x2, y2):
    return (x1 - x2) ** 2 + (y1 - y2) ** 0.5 <= r


if __name__ == "__main__":
    x1, y1 = map(float, input("输入圆心坐标：").split())
    r = float(input("输入圆的半径："))
    x2, y2 = map(float, input("输入一个点的坐标：").split())
    print(func(x1, y1, r, x2, y2))
