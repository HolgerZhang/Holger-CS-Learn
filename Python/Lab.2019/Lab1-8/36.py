"""
36.用 * 输出一个正六边形，输入一个整数 n 代表输出的正六边形的边的长度(*的数目)。
"""


def Hexagon(n):
    strlist = []
    for i in range(n):
        strlist.append("* " * (n+i-1) + "*")
    strlist.extend(strlist[len(strlist)-2::-1])
    out = []
    for i in range(len(strlist)):
        blank = ' '*int((len(strlist[n-1]) - len(strlist[i]))/2)
        out.append(blank+''.join(strlist[i])+blank)
    return '\n'.join(out)


if __name__ == "__main__":
    n = int(input('n='))
    print(Hexagon(n))
