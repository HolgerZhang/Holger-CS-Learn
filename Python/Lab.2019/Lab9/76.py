"""
76. 当前路径下有文本文件 Numbers.txt，文件中的每一行都是一个浮点数，编写程序读取出所有的浮点数。要求：
    a) 从小到大排序，将排序后的结果写到当前路径下新生成的一个文本文件Sort.txt 中，每个数占一行。
    b) 求出这些数字的均值、方差，将结果写到当前路径下新生成的一个文本文件 Sort.txt 中，每个数占一行。
    c) 要求生成的文本文件 Sort.txt 中同时包含排序和均值、方差的结果。
"""


def get_float(raw_name, new_name):
    formatter = lambda num: str(num) + '\n'
    write_list = []
    num_list = []

    with open(raw_name) as file_raw:
        while True:
            number = file_raw.readline()
            if not number:
                break
            num_list.append(float(number))

    # sort
    num_list.sort()
    write_list.extend(map(formatter, num_list))
    # aver and s2
    aver = sum(num_list) / len(num_list)
    write_list.append(formatter(aver))
    s2 = 0
    for num in num_list:
        s2 += (num - aver) ** 2
    s2 /= len(num_list)
    write_list.append(formatter(s2))

    with open(new_name, "w") as file_new:
        file_new.writelines(write_list)


if __name__ == "__main__":
    get_float(r"Numbers.txt", r"Sort.txt")
