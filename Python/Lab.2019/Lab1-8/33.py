"""
33. 从键盘输入一个字母，如果输入的是小写英文字母，请将其转换为大写字母
    后显示输出；如果输入的是大写英文字母，请将其转换为小写字母后显示输
    出；如果既不是小写英文字母、也不是大写英文字母，则原样显示。
"""


def func(inchr):
    newchr = inchr.upper()
    return newchr if newchr != inchr else inchr.lower()


if __name__ == "__main__":
    inchr = input("请输入一个字符:")
    print(func(inchr))
