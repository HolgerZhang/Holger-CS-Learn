"""
19. 用筛法求 500 之内的所有质数，并打印输出所有的质数，每行输出 5 个质数
"""


def allPrime(n):
    total = list(range(n+1))
    PrimeList = []
    for i in range(len(total)):
        if total[i] == 2:
            PrimeList.append(total[i])
        elif total[i] > 2:
            for j in range(len(PrimeList)):
                if total[i] % PrimeList[j] != 0:
                    if j == len(PrimeList) - 1:
                        PrimeList.append(total[i])
                else:
                    break
        else:
            continue
    return PrimeList


def Display(PrimeList):
    for i in range(0, len(PrimeList)):
        print("%d" % PrimeList[i], end="\t")
        if (i + 1) % 5 == 0:
            print("")


if __name__ == "__main__":
    Display(allPrime(500))
