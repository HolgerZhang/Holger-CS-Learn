"""
32. 假设银行对 1 年期的存款利息计算法方法如下：如果存款金额 I 小于 10 万
    元，则按照 1.5%的年利率计算利息；如果存款金额 I 大于等于 10 万元，但
    小于 50 万元，则按照 2%的年利率计算利息；如果存款金额 I 大于等于 50
    万元，但小于 100 万元，则按照 3%的年利率计算利息；如果存款金额大于
    等于 100 万元，则按照 3.5%的年利率计算利息。现在从键盘输入一个整数
    表示存款金额，请计算一年后的本金和利息总共有多少，将计算结果输出到
    屏幕上。
"""


def deposit(money):
    if money < 100000:
        rate = 0.015
    elif 100000 <= money < 500000:
        rate = 0.02
    elif 500000 <= money < 1000000:
        rate = 0.03
    else:
        rate = 0.035
    return money * (1 + rate)


if __name__ == "__main__":
    money = int(input("请输入存款金额(元):"))
    print("一年后的本金和利息总共%f元" % deposit(money))
