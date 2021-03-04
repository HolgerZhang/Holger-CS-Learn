"""
26. 从键盘输入三个浮点数 a、b 和 c，求解 ax2+bx+c=0 的解，并将结果输出
    到屏幕上。在求解过程中，需要考虑 a 等于 0 的无意义情况并给出相应提示
    信息，同时需要考虑有实数解和无实数解的两种不同的情况。（注：当有实数
    解时不允许使用复数形式来表示结果）。结果（含负数解的实部和虚部）的显
    示格式要求为：小数部分 5 列（不含小数点），整个数占 10 列。
"""


def equation(a, b, c):
    if a == 0:
        return None
    delta = b ** 2 - 4 * a * c
    return ((-b - delta ** 0.5) / (2 * a),
            (-b + delta ** 0.5) / (2 * a))


def display(result):
    if result:
        x1, x2 = result
        if isinstance(x1, complex):
            print('x1={0.real:10.5f}{0.imag:+10.5f}j'.format(x1))
            print('x2={0.real:10.5f}{0.imag:+10.5f}j'.format(x2))
        else:
            if x1 != x2:
                print("x1=%10.5f" % x1)
                print("x2=%10.5f" % x2)
            else:
                print("x1=x2=%10.5f" % x1)
    else:
        print("The number 'a' cannot be 0.")


if __name__ == "__main__":
    a = float(input('a='))
    b = float(input('b='))
    c = float(input('c='))
    display(equation(a, b, c))
