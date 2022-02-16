# coding=utf-8
import sys
from time import sleep

import translation
from py_yacc import yacc

if len(sys.argv) != 2:
    print('不正确的用法', file=sys.stderr)
    exit(1)

try:
    with open(sys.argv[-1], 'r', encoding='utf-8') as file:
        text = file.read()
    # syntax parse
    root = yacc.parse(text)
    print("分析前的语法树：", root)
    if root is None:
        exit(0)
    # translation
    print('运行结果：')
    translation.translate(root)
    print("分析后的语法树：", root)
    print("当前变量表：", translation.var_table)
except Exception as e:
    sys.stdout.flush()
    sleep(0.05)
    print(*e.args, file=sys.stderr)