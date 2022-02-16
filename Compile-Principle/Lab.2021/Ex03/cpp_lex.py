# -*- coding: utf-8 -*-

import sys

import ply.lex as lex


class CPlusPlusLexer:
    def __init__(self):
        self.lexer = None

    # ------------------------------------------------------------
    # 预定义常量
    # ------------------------------------------------------------

    # 保留字
    reserved_words = {
        'if': 'IF',
        'while': 'WHILE',
        'int': 'INT',
        'cout': 'COUT',
        'endl': 'ENDL',
    }

    # token 列表
    tokens = ['NUMBER', 'PLUS', 'MINUS', 'TIMES', 'DIVIDE', 'LPAREN', 'RPAREN', 'INSERT', 'ASSIGN',
              'LT', 'GT', 'LBRACE', 'RBRACE', 'SEMICOLON', 'STRING', 'ID'] + list(reserved_words.values())

    # ------------------------------------------------------------
    # 正则表达式声明
    # ------------------------------------------------------------

    # 普通 token 的正则表达式定义
    t_PLUS = r'\+'
    t_MINUS = r'-'
    t_TIMES = r'\*'
    t_DIVIDE = r'/'
    t_LPAREN = r'\('
    t_RPAREN = r'\)'
    t_LBRACE = r'\{'
    t_RBRACE = r'\}'
    t_ASSIGN = r'='
    t_INSERT = r'<<'  # 流插入运算符
    t_LT = r'<'
    t_GT = r'>'
    t_SEMICOLON = r';'

    # 识别字符串，解决 "string" <token> "string" 情况下匹配不到两个字符串的问题
    def t_STRING(self, t):
        r'"(.*)"'
        start, end = t.lexer.lexmatch.span()  # 匹配到的位置
        # 找到第一个结束引号的位置：除第一个引号外，首次出现的不在\字符后面的引号
        for i in range(start, end + 1):
            if t.lexer.lexdata[i] == '"':
                if i == start:
                    continue
                if t.lexer.lexdata[i - 1] == '\\':
                    continue
                end = i
                break
        t.lexer.lexpos = end + 1  # 修改（提前）分析点
        t.value = t.lexer.lexdata[start:end + 1]  # 修改数据
        return t

    # 识别 ID，首先检查是否为保留字，若是则申明其类型为相应保留字，否则为 ID
    def t_ID(self, t):
        r'[a-zA-Z]+'
        t.type = self.reserved_words.get(t.value, 'ID')
        return t

    # 识别数字
    def t_NUMBER(self, t):
        r'\d+'
        t.value = int(t.value)
        return t

    # 识别新行，并将行号 + 1
    def t_newline(self, t):
        r'\n+'
        t.lexer.lineno += len(t.value)

    # 忽略的字符
    t_ignore = ' \t'

    # 错误处理程序
    def t_error(self, t):
        print("\nInvalid token '%s' at line %d" % (t.value[0], t.lexer.lineno), file=sys.stderr)
        t.lexer.skip(1)

    # ------------------------------------------------------------
    # 构建与使用
    # ------------------------------------------------------------

    # 构建 lex
    def build(self, **kwargs):
        self.lexer = lex.lex(module=self, **kwargs)

    # token 迭代器
    def lex_tokens(self, data: str):
        if self.lexer is None:
            raise ValueError('lexer should have been built first!')
        self.lexer.input(data)
        while True:
            tok = self.lexer.token()
            if not tok:
                break
            yield tok


# ------------------------------------------------------------
# 辅助函数
# ------------------------------------------------------------


# 读文件
def read_file(path: str) -> str:
    with open(path, 'r', encoding='utf-8') as f:
        s = f.read()
    return s


# ------------------------------------------------------------
# 程序入口
# ------------------------------------------------------------

if __name__ == '__main__':
    if len(sys.argv) == 2:
        source = read_file(sys.argv[1])
    else:
        source = sys.stdin.read()
    # 构建 lex
    lexer = CPlusPlusLexer()
    lexer.build()
    # 为 lexer 提供输入数据，输出词法单元，同一行的词法单元输出在一行
    line = 1
    for token in lexer.lex_tokens(source):
        if line != token.lineno:
            line = token.lineno
            print()
        print('<%s, %r>' % (token.type, token.value), end=' ')
    print()
