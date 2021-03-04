"""
40. 矩阵相加：提示用户输入一个数字 n，为矩阵的行数，再提示用户输入一个
    数字 m，为矩阵的列数，接下来，提示用户输入 2*n*m 个数字（每次输入
    一个数字）。输出 C=A+B。
"""


def plusit(A, B):
    A_row, A_col = len(A), len(A[0])
    B_row, B_col = len(B), len(B[0])
    if A_col != B_col or A_row != B_row:  # 不能运算
        return None
    result = [[A[row][col] + B[row][col] for col in range(A_col)] for row in range(A_row)]
    return result


def getnum(n, m):
    A = [[0 for i in range(m)] for j in range(n)]
    B = [[0 for i in range(m)] for j in range(n)]
    for i in range(n):
        for j in range(m):
            A[i][j] = int(input('Please input A[%d,%d]:' % (i,j)))
    for i in range(n):
        for j in range(m):
            B[i][j] = int(input('Please input B[%d,%d]:' % (i,j)))
    return A, B


if __name__ == "__main__":
    n = int(input("n = "))
    m = int(input("m = "))
    print(plusit(*getnum(n, m)))
