"""
24. 打印 n 阶魔方阵（n 为奇数）。魔方阵的每一行、每一列和两个对角线的和都相等。
"""


def magic_matrix(n):
    origin = list(range(1, n*n+1))
    magic = [[None for j in range(n)] for k in range(n)]  # 空方阵

    def save(L, V, i):
        """ 写入数据并保存位置 """
        magic[L][V] = origin[i]
        return L, V  # 保存上一次数据

    # 预规则：把1放在第一行中间一列
    L, V = 0, n // 2
    rL, rV = save(L, V, 0)

    for i in range(1, len(origin)):
        if rL == 0 and rV == n - 1: L, V = rL + 1, rV      # 上一行是第1行第n列，放在下面
        elif rL == 0:               L, V = n - 1,  rV + 1  # 上一个行数为1，下一个行数为n
        elif rV == n-1:             L, V = rL - 1, 0       # 上一个列数为n，下一个列数为1，行数减1
        else:                       L, V = rL - 1, rV + 1  # 其他情况：行数减1，列数加1
        if magic[L][V]:             L, V = rL + 1, rV      # 以上规则已经有数，放在下面
        rL, rV = save(L, V, i)  # 写入
    return magic


def Display(matrix):
    for i in matrix:
        for j in i:
            print(j, end="\t")
        print('')


if __name__ == "__main__":
    n = int(input('请输入一个奇数：'))
    Display(magic_matrix(n))
