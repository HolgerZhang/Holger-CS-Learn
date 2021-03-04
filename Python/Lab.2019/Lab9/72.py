"""
72.当前路径下有文本文件 copy.txt，编写程序实现文本文件的复制功能。（在当
    前路径下新建一个 new.txt 文件,将文本文件 copy.txt 的内容复制到 new.txt
    文件中）
"""


def copy_files(f1, f2):
    # open
    file_raw = open(f1)
    file_copy = open(f2, "w")
    # copy
    text = file_raw.read()
    file_copy.write(text)
    # close
    file_copy.close()
    file_raw.close()


if __name__ == "__main__":
    copy_files(r"copy.txt", r"new.txt")
