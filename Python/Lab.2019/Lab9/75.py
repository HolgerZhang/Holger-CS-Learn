"""
当前路径下有一个文本文件 students_data.txt，该文件中保存了若干个学生的信息，
每个学生信息占一行，学生信息从左到右分别为：学号(int 类型)、姓名(字符串类型)、
年级(int 类型)，各学生信息以空格分隔。编写程序完成如下功能：
    (1) 读取所有学生信息。
    (2) 输出所有学生信息到屏幕上，要求每个学生信息占一行，学号占 10 列、
        左对齐，姓名占 15 列、左对齐，年级占 5 列、右对齐。
    (3) 对所有学生根据其学号按照从小到大排序。
    (4) 删除学号小于指定值 s1 的所有学生，其中 s1 由键盘输入。

"""


def read_file(file_name):
    result = []
    with open(file_name, encoding="UTF-8") as file_raw:
        while True:
            line = file_raw.readline()
            if not line:
                break
            student = line.split()
            result.append((int(student[0]), student[1], int(student[2])))
    return result


def display(obj):
    formatter = '{0:<10d}{1:<15s}{2:5d}'.format
    for item in obj:
        print(formatter(*item))


def sort_students(lst):
    lst = lst[:]
    lst.sort(key=lambda x: x[0])
    return lst


def remove_students(s1, lst):
    res = []
    for item in lst:
        if item[0] >= s1:
            res.append(item)
    return res


def write_file(file_name, obj):
    with open(file_name, "w", encoding="UTF-8") as file_write:
        for item in obj:
            line = ' '.join(map(str, item)) + "\n"
            file_write.write(line)


if __name__ == "__main__":
    students = read_file(r"students_data.txt")
    print("学生信息:")
    display(students)
    students = sort_students(students)
    s1 = int(input("请输入s1:"))
    students_new = remove_students(s1, students)
    write_file(r"students_data.txt", students_new)
    print("排序并删除后剩余的学生已经写入\"students_data.txt\"")
