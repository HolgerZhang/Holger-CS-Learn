def isDDPI(num):    # 判断水仙花数
    return sum(map(lambda x: int(x) ** 3, str(num))) == num if len(str(num)) == 3 else None


if __name__ == "__main__":
    # 找出水仙花数
    lst = []
    for i in range(100,1000):
        if isDDPI(i):
            lst.append(i)

    print(lst)