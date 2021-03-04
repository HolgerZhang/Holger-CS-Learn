"""
    矩阵有关固定解法
    index:
        ## 矩阵相乘（简化版）: func3_2018_2(A, B)
        ## 矩阵相乘: multiple(A, B)
        ## 矩阵相加: multiple(A, B)
"""


def func3_2018_2(A, B):
    """
    2018-2
    ## 矩阵相乘（简化版）
    :param A, B: 两个矩阵分别严格满足m*d和d*n的形状（m>=1, d>=1, n>=1），矩阵中的元素均为整数。
    :return: 相乘后的矩阵，用二维列表表示
    """
    A_row, A_col = len(A), len(A[0])
    result = []
    BT = [list(row) for row in zip(*B)]
    for Ai in range(A_row):
        rowItem = []
        for Bi in range(len(BT)):
            num = 0
            for Bj in range(len(BT[Bi])):
                num += A[Ai][Bj] * BT[Bi][Bj]
            rowItem.append(num)
        result.append(rowItem)
    return result


def multiple(A, B):
    """
    ## 矩阵相乘
    """
    A_row, A_col = len(A), len(A[0])
    B_row, B_col = len(B), len(B[0])
    if A_col != B_row:  # 不能运算
        return None
    result = []
    # zip解包后是转置的元组，转换成list放到result中
    BT = [list(row) for row in zip(*B)]  ## 矩阵转置
    for Ai in range(A_row):  # 相乘开始
        rowItem = []  # 新的行
        for Bi in range(len(BT)):
            num = 0  # 累加
            for Bj in range(len(BT[Bi])):
                num += A[Ai][Bj] * BT[Bi][Bj]
            rowItem.append(num)  # 累加完成后存入新矩阵的行中
        result.append(rowItem)
    return result


def plusit(A, B):
    """
    ## 矩阵相加
    """
    A_row, A_col = len(A), len(A[0])
    B_row, B_col = len(B), len(B[0])
    if A_col != B_col or A_row != B_row:  # 不能运算
        return None
    result = [[A[row][col] + B[row][col] for col in range(A_col)] for row in range(A_row)]
    return result

if __name__ == "__main__":
    """ 测试用例 """
    print(func3_2018_2([[1, 2]],
                       [[1], [2]]))  # [[5]]
    print(multiple([[1, 2], [1, 3]],
                   [[1, 1], [1, 0]]))  # [[3, 1], [4, 1]]
    print(multiple([[1, 2], [1, 3]],
                   [[1, 2, 3]]))  # None
    print(plusit([[1, 2], [1, 3]],
                 [[1, 1], [1, 0]]))  # [[2, 3], [2, 3]]
    print(plusit([[1, 2], [1, 3]],
                 [[1], [1]]))  # None
