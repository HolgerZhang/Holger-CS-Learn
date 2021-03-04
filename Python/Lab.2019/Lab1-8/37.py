"""
37. 提示用户输入一个整型数字 n（n 代表后续需要输入整型数的数量），将 n 个
    整型数加起来并输出，如果输入的是非整型数则提示当前的输入非法需要重
    新输入数值，如果输入‘n=0’代表退出程序，否则继续提示用户输入新的n。
"""


def numplus():
    while True:
        while True:
            try: n = int(input('Please input the number of numbers:'))
            except ValueError: pass
            else: break
        if n == 0: break
        s = 0
        for i in range(n):
            while True:
                try: s += int(input('Please input number%d:' % (i+1)))
                except ValueError: pass
                else: break
        print("sum =", s)


if __name__ == "__main__":
    numplus()

