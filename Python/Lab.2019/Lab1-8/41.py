"""
41. 有 n 个小朋友围成一圈玩游戏，小朋友从 1 至 n 编号，2 号小朋友坐在 1 号
    小朋友的顺时针方向，3 号小朋友坐在 2 号小朋友的顺时针方向，……，1 号
    小朋友坐在 n 号小朋友的顺时针方向。
    从 1 号小朋友开始顺时针报数，接下来每个小朋友的报数是上一个小朋
    友报的数加 1。若一个小朋友报的数为 k 的倍数，则该小朋友被淘汰出局，
    不再参加以后的报数。当游戏中只剩下一个小朋友时，该小朋友获胜。
     例如，当 n=5, k=2 时：
         1 号小朋友报数 1；
         2 号小朋友报数 2 淘汰；
         3 号小朋友报数 3；
         4 号小朋友报数 4 淘汰；
         5 号小朋友报数 5；
         1 号小朋友报数 6 淘汰；
         3 号小朋友报数 7；
         5 号小朋友报数 8 淘汰；
         3 号小朋友获胜。
    让用户给定 n 和 k，请问最后获胜的小朋友编号为多少？
"""
from itertools import cycle


def kidgame(n, k):
    kids = cycle(range(1, n+1))
    flag = 0
    die = set()
    while True:
        kid = next(kids)
        if kid in die:
            continue
        if n == 1:
            return kid
        flag += 1
        if flag % k == 0:
            die.add(kid)
            n -= 1


if __name__ == "__main__":
    n = int(input("The number of kids:"))
    k = int(input('k='))
    print('The winner is kid%d.' % kidgame(n, k))
