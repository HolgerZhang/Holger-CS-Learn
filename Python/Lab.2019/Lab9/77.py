"""
77. 当前路径下有一个文件夹 Folder，文件夹下有多个文本文件 file1~file4（文件名称和文件内容都是英文的），
    将这些文本文件内容合并生成一个新的文本文件 merge.txt 存放在 Folder 文件夹中，不破坏原始文件。
"""


if __name__ == "__main__":
    with open(r"Folder/merge.txt", "w") as file_sum:
        for i in range(1, 5):
            with open(r"Folder/file%d.txt" % i) as file_temp:
                file_sum.write(file_temp.read())
                file_sum.write('\n')
