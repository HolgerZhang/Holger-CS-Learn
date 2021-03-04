"""
34. 用 * 输出一个等腰三角形。提示用户输入一个整数 n，代表输出的等边三角
    形由 n 行 * 组成。
"""


def func(n):
    tri = []
    for i in range(1, n + 1):
        tri.append(' '*(n-i)+'*'*(2*i-1)+' '*(n-i))
    return '\n'.join(tri)


if __name__ == "__main__":
    print(func(int(input('n='))))
