import re

def func1(m, n):
    if m<=1 or n<=1:return None
    else:
        for i in range(2,min(m,n)+1):
            if m%i == 0 and n%i == 0:
                return False
        return True

def func2(lst):
    lst=lst[:]
    if len(lst)<=1:return 0
    else:
        a=0
        for i in range(len(lst)-1):
            for j in range(i+1,len(lst)):
                if lst[i]>lst[j]:
                    a+=1
        return a

def func3(A, B):
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

def func4(lst):
    n = int(len(lst)**0.5)
    return [lst[0+i*n:n+i*n] for i in range(n)]

def func5(sentence):
    lst=sentence.split()
    sDict=dict()
    for x in lst:
        sDict[x]=lst.count(x)
    lst.sort(key=lambda x:(sDict[x],x),reverse=True)
    for i in range(len(lst)-1,0,-1):
        if lst.count(lst[i])>1:
            lst.pop(i)
    if len(lst)<=3:return lst
    else:return lst[:3]

def func6(S, T):
    a=len(set((i for i in S if i in T)))
    b=len(set((i for i in S if i not in T)))
    c=len(set((i for i in T if i not in S)))
    return (a, b, c)

def func7(string1):
    string1=string1.upper()
    sDict = dict()
    for x in list(string1):
        sDict[x] = list(string1).count(x)
    return list(max(list(sDict.items()),key=lambda x:x[1]))

def func8(string1):
    lst = [i for i in re.split('\D+',string1) if len(i)>=3 and len(i)<=5]
    lst.sort(key=lambda x:sum(list(map(int,list(x))))/len(x),reverse=True)
    return list(map(int,lst))

if __name__ == "__main__":
    print(func1(2,3))
    print(func1(3,6))
    print(func2([4,3,2,1]))
    print(func2([4,1,2,3]))
    print(func3([[1,2]],[[1],[2]]))
    print(func3([[1,2],[1,3]],[[1,1],[1,0]]))
    print(func4([1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6]))
    print(func5('hello hi hello apple'))
    print(func5('a'))
    print(func6('his', 'she'))
    print(func6('hello', 'python'))
    print(func7("1aA"))
    print(func8('123a4567 1'))
    print(func8('1234'))
    print(func8('1234 sdjfh59832234 4958 sdj3 323n5555k5 m3 334'))
