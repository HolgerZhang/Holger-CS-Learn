# coding=utf-8
import sys

from ply import lex

# LEX for parsing Python

# Tokens
tokens = ('ID', 'NUMBER', 'PRINT')

literals = ['=', '+', '-', '*', '/', '(', ')', '{', '}', '<', '>', ',']
reserved_words = {
    'print': 'PRINT',
}


# Define of tokens

# 识别 ID，首先检查是否为保留字print，若是则申明其类型，否则为 ID
def t_ID(t):
    r"""[A-Za-z_][A-Za-z0-9_]*"""
    t.type = reserved_words.get(t.value, 'ID')
    return t


# 识别新行，并将行号 + 1
def t_newline(t):
    r"""\n+"""
    t.lexer.lineno += len(t.value)


def t_NUMBER(t):
    r"""-?[0-9]+"""
    t.value = int(t.value)
    return t


# 忽略的字符
t_ignore = ' \t'


# 错误处理程序
def t_error(t):
    print("\nInvalid token '%s' at line %d" % (t.value[0], t.lexer.lineno), file=sys.stderr)
    t.lexer.skip(1)


lex.lex()
