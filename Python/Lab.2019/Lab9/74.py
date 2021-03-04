"""
74. 当前路径下有文本文件 StrInts.txt，该文件中有一段英文文章，在该文章中存在一些整数（有正有负）。
    编写程序读取该文件、并提取出其中所有的整数，然后将这些整数中偶数位数字上全部都为奇数数字的整数
    保存到当前路径的ResultInts.txt 文件中去，保存时每行 3 个数、每个数占 8 列、右对齐左补空格。
"""
import re


def is_result(n):
    if n in range(-9, 10):
        return False
    lst = list(map(int, str(abs(n))))
    for i in range(len(lst)):
        if (i + 1) % 2 == 0:
            if lst[i] % 2 == 0:
                return False
    return True


def find_numbers(text):
    # find
    pattern = re.compile('-?\d+')
    all_int = list(map(int, pattern.findall(text)))
    res = []
    for number in all_int:
        if is_result(number):
            res.append(number)
    # save
    ans = []
    reformat = '{0:8d}'.format
    for i in range(len(res) // 3 + 1):
        temp = ''.join(map(reformat, res[3 * i:3 * (i + 1)])) + '\n'
        ans.append(temp)
    return ans


def write_file(file_name, new_file_name):
    with open(file_name, encoding="UTF-8") as file_raw:
        text = file_raw.read()
    ans = find_numbers(text)
    with open(new_file_name, "w") as file_result:
        for s in ans:
            file_result.write(s)


if __name__ == "__main__":
    write_file(r"StrInts.txt", r"ResultInts.txt")