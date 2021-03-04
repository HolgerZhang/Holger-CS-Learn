"""
79. 当前路径下有一个文本文件 Names.txt，包含了按照字典序排序的名字。编写一个程序，当用户自己
    给定一个名字，按照字典序将其插入到正确的位置。如果这个名字已经存在于文件中，则不要插入。
"""


def insert_name(new_name, flie_name, file_new):
    with open(flie_name) as file_raw:
        new = []
        while True:
            name = file_raw.readline()
            if not name:
                new.append("\n" + new_name)
                break
            temp = name.rstrip()
            if new_name > temp:
                new.append(name)
                continue
            if new_name == temp:
                new.append(name)
                new.append(file_raw.read())
                break
            if new_name < temp:
                new.append(new_name + "\n")
                new.append(name)
                new.append(file_raw.read())
                break
    with open(file_new, 'w') as file_new:
        file_new.writelines(new)


if __name__ == "__main__":
    s = input("插入的名字:")
    insert_name(s, r"Names.txt", r"Names.txt")
