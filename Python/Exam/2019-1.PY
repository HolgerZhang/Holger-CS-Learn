#  学号:1927405160
#  姓名:张昊
#  IP:192.168.158.157
#  上传时间:2019/11/6 19:27:04

def func1(n):
    if n >= 60:
        return True
    else:
        return False

def func2(n):
    five = 0
    three = 0
    if n >= 50:
        five = n // 50
        n = n % 50
    if n >= 30:
        three = n // 30
        n = n % 30
    one = n // 10
    s = one + three*4 + five*8
    return s

def func3(n):
    s=0
    for i in range(2,n,2):
        s += i**2
    return s

def func4(k):
    n=0
    for x in range(0,k+1):
        for y in range(0,k+1):
            if x+y*2 < k:
                n += 1
    return n

def func5(a, b):
    if a%b == 0 or b%a == 0:
        return True
    else:
        return False

def func6(x):
    return bin(x).count('1')

def func7(lst):
    if len(lst) >= 3:
        lst = lst[::]
        lst.sort()
        lst.pop()
        lst.sort(reverse=True)
        lst.pop()
        average = sum(lst)//len(lst)
        return average
    else:
        return None

def isprime(n):
    if n>=2:
        for i in range(2,n):
            if n%i == 0:
                return False
        else:
            return True
    else:
        return False

def func8(lst):
    new = []
    for i in range(len(lst)):
        if lst[i]<100:
            continue
        else:
            numi = list(map(int,list(str(lst[i]))))
            back2 = int(''.join(list(map(str,numi[-2:]))))
            other = int(''.join(list(map(str,numi[:-2]))))
            if isprime(back2) and isprime(other):
                new.append(lst[i])
    return new

if __name__ == '__main__':
    print(func8([2, 203, 9797]))
    print(func8([2, 97, 9797]))
    print(func8([7]))
    print(func8([2, 1097, 203, 197, 212, 1037]))

    '''for i in range(10):
        print(i,end=' ')
        print(isprime(i))'''

    pass
    '''print(func7([1,2]))
    print(func7([55,33,66,77,22,3,1,1]))
    print(func7([1,3,5,6,4,2]))'''
    pass
    '''print(func6(10))
    print(func6(5))
    print(func6(100))
    print(func6(30))'''
    pass
    '''print(func5(2,4))
    print(func5(3,5))
    print(func5(1,2))'''
    pass
    '''print(func4(1))
    print(func4(2))
    print(func4(3))
    print(func4(0))
    print(func4(-1))'''
    pass
    '''print(func3(3))
    print(func3(5))
    print(func3(7))
    print(func3(9))'''
    pass
    '''print(func2(140))
    print(func2(91))
    print(func2(31))
    print(func2(51))
    print(func2(20))'''
    pass
    '''print(func1(60))
    print(func1(50))
    print(func1(90))'''
    pass

