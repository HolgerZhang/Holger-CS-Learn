"""
10. 请编写一个程序显示当前北京时间，要求显示格式如下：
    当前时间是：几时：几分：几秒
    输出示例：当前时间是： 14：26：32
"""
import time


def nowtime():
    return "%02d:%02d:%02d" % (time.localtime()[3],
                               time.localtime()[4],
                               time.localtime()[5])


if __name__ == "__main__":
    print("当前时间是：", nowtime())