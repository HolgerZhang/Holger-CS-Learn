"""
78. 当前路径下有文本文件 word.txt 中包含了 20 个英文单词，编写一个程序，
    删除文件中所有不以元音开头的单词。结果保存在当前路径下新生成的new_word.txt 中。
"""
import re


def find_words(raw_name):
    with open(raw_name) as file_raw:
        text = file_raw.read()
    pattern = re.compile("\\b[^AEIOUaeiou\n]\w*\\b")
    result = pattern.findall(text)
    return result


def write_word(result, new_name):
    write_list = [x + "\n" for x in result]
    with open(new_name, "w") as file_new:
        file_new.writelines(write_list)


if __name__ == "__main__":
    res = find_words(r"word.txt")
    write_word(res, r"new_word.txt")
