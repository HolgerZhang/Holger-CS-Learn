"""
15. 请计算当前距离 1970 年 1 月 1 日过去了多少天又多少小时，并输出到屏幕上
"""
import time


def timenow():
    a = time.time()
    day = int(a // 86400)
    hour = int((a-day*86400)//3600)
    return day, hour


if __name__ == "__main__":
    print("当前距离1970年1月1日过去了%d天又%d小时" % timenow())
