"""
语法：
program : statements
statements : statements statement | statement
statement : assignment | expr | print
assignment : ID '=' expr
expr : expr '+' term | expr '-' term | term
term : term '*' factor | term '/' factor | factor
factor : ID | NUMBER | '(' expr ')'
exprs : exprs ',' expr | expr
print : PRINT '(' exprs ')' | PRINT '(' ')'
"""

# coding=utf-8
from ply import yacc
from py_lex import *
from node import *


# YACC for parsing Python


def p_program(t):
    """program : statements"""
    if len(t) == 2:
        t[0] = NonTerminal('Program')
        t[0].add(t[1])


def p_statements(t):
    """statements : statements statement
                  | statement"""
    if len(t) == 3:
        t[0] = NonTerminal('Statements')
        t[0].add(t[1])
        t[0].add(t[2])
    elif len(t) == 2:
        t[0] = NonTerminal('Statements')
        t[0].add(t[1])


def p_statement(t):
    """ statement : assignment
                  | expr
                  | print"""
    if len(t) == 2:
        t[0] = NonTerminal('Statement')
        t[0].add(t[1])


def p_assignment(t):
    """assignment : ID '=' expr"""
    if len(t) == 4:
        t[0] = NonTerminal('Assignment')
        t[0].add(ID(t[1]))
        t[0].add(Terminal(t[2]))
        t[0].add(t[3])


def p_expr(t):
    """expr : expr '+' term
            | expr '-' term
            | term"""
    if len(t) == 4:
        t[0] = NonTerminal('Expr')
        t[0].add(t[1])
        t[0].add(Terminal(t[2]))
        t[0].add(t[3])
    elif len(t) == 2:
        t[0] = NonTerminal('Expr')
        t[0].add(t[1])


def p_term(t):
    """term : term '*' factor
            | term '/' factor
            | factor"""
    if len(t) == 4:
        t[0] = NonTerminal('Term')
        t[0].add(t[1])
        t[0].add(Terminal(t[2]))
        t[0].add(t[3])
    elif len(t) == 2:
        t[0] = NonTerminal('Term')
        t[0].add(t[1])


def p_factor(t):
    """factor : ID
              | NUMBER
              | '(' expr ')' """
    if len(t) == 4:
        t[0] = NonTerminal('Factor')
        t[0].add(Terminal(t[1]))
        t[0].add(t[2])
        t[0].add(Terminal(t[3]))
    elif len(t) == 2:
        t[0] = NonTerminal('Factor')
        if isinstance(t[1], int) or t[1].isdigit():
            t[0].add(Number(t[1]))
        else:
            t[0].add(ID(t[1]))


def p_exprs(t):
    """exprs : exprs ',' expr
             | expr"""
    if len(t) == 4:
        t[0] = NonTerminal('Exprs')
        t[0].add(t[1])
        t[0].add(Terminal(t[2]))
        t[0].add(t[3])
    elif len(t) == 2:
        t[0] = NonTerminal('Exprs')
        t[0].add(t[1])


def p_print(t):
    r"""print : PRINT '(' exprs ')'
              | PRINT '(' ')' """
    if len(t) == 5:
        t[0] = NonTerminal('Print')
        t[0].add(Terminal(t[1]))
        t[0].add(Terminal(t[2]))
        t[0].add(t[3])
        t[0].add(Terminal(t[4]))
    elif len(t) == 4:
        t[0] = NonTerminal('Print')
        t[0].add(Terminal(t[1]))
        t[0].add(Terminal(t[2]))
        t[0].add(Terminal(t[3]))


def p_error(t):
    if t is None:
        raise SyntaxError("Syntax error")
    raise SyntaxError("Syntax error '%s' at line %d" % (t.value[0], t.lexer.lineno))


yacc.yacc()
