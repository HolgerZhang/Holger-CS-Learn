"""
23. 现有 5 名同学期中考试高数和线代成绩如下：
    姓名 高数 线代
    张飞 78 75
    李大刀 92 67
    李墨白 84 88
    王老虎 50 50
    雷小米 99 98
    编写程序按照总分从高到低进行排序后输出姓名和成绩。
"""


def get_marks(n):
    marks = []
    for i in range(n):
        name = input("姓名：")
        math1 = int(input("高数成绩："))
        math2 = int(input("线代成绩："))
        marks.append([name, math1, math2])
    return marks


def SortSum(marks):
    new = [[student[0], sum(student[1:])] for student in marks]
    return sorted(new, key=lambda x: x[1], reverse=True)


def Display(result):
    print("总成绩排名如下：")
    for i in range(len(result)):
        print('%s\t分数为：%d' % (result[i][0], result[i][1]))


if __name__ == "__main__":
    marks = get_marks(5)
    sum_marks = SortSum(marks)
    Display(sum_marks)
