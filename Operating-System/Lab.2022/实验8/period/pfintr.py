#!/bin/python3
import re
import sys
import time


def get_page_fault():
    """ 得到当前系统的缺页中断次数 """
    pgfault = -1
    with open('/proc/vmstat', 'r') as vmstat:
        # 通过正则表达式提取pgfault的值
        match = re.search(r'pgfault\s(\d+)', vmstat.read())
        if match:
            pgfault = int(match.group(1))
    return pgfault


calc_time = 5  # 休眠时间
if len(sys.argv) >= 2 and sys.argv[1].isdigit():
    calc_time = int(sys.argv[1])
print("Use time: {}s".format(calc_time))
pgfault1 = get_page_fault()
if pgfault1 < 0:
    print('read file error!')
    exit(1)
print("Now the number of page fault is {}".format(pgfault1))
time.sleep(calc_time)  # 进程休眠
pgfault2 = get_page_fault()
if pgfault2 < 0:
    print('read file error!')
    exit(1)
print("Now the number of page fault is {}".format(pgfault2))
page_fault = pgfault2 - pgfault1
print("In {} seconds, system calls {} page fault!"
      .format(calc_time, page_fault))
