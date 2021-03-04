"""
68. 创建一个有关雇员姓名和编号处理的程序。从键盘输入一组雇员姓名和编号。
    在此基础上实现：
    a)  按照雇员姓名的顺序输出数据，雇员姓名显示在前面，后面是对应的雇员编号。
    b)  按照雇员编号的顺序输出数据，雇员编号显示在前面，后面是对应的雇员姓名。
"""


def getInformation():
    information = dict()
    print("注：若编号为空则结束输入。")
    while True:
        number = input("请输入编号：")
        if not number:
            break
        number = int(number)
        if information.get(number):
            print("编号已占用，请重新输入")
            continue
        Name = input("请输入姓名：")
        information[number] = Name
    print()
    return information


def Display(info_dict, name_order=False):
    s = list(info_dict.items())
    if name_order:
        s.sort(key=lambda x: x[1])
        for i in range(len(s)):
            print(s[i][1], end='\t')
            print(s[i][0])
    else:
        s.sort(key=lambda x: x[0])
        for i in range(len(s)):
            print(s[i][0], end='\t')
            print(s[i][1])


if __name__ == "__main__":
    employees = getInformation()
    print('按姓名排序：')
    Display(employees, name_order=True)
    print('按编号排序：')
    Display(employees)
