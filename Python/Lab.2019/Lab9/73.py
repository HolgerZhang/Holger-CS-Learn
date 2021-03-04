"""
73. 当前路径下有两个文本文件 cat1.txt 和 cat2.txt，编写程序将 cat2.txt 文件中的内容添加到 cat1.txt 文件中。
"""


def append_file(f1, f2):
    # open
    file_1 = open(f1, "a")
    file_2 = open(f2)
    # append
    text = file_2.read()
    file_1.write(text)
    # close
    file_1.close()
    file_2.close()


if __name__ == "__main__":
    append_file(r"cat1.txt", r"cat2.txt")
