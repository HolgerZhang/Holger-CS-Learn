# coding=utf-8
from node import *

var_table = {}  # variable table


def translate(tree):
    # 深度优先遍历语法树
    for child in tree.children:
        translate(child)

    # Translation
    if isinstance(tree, NonTerminal):
        # Assignment
        if tree.type == 'Assignment':
            '''assignment : ID '=' expr'''
            assert len(tree.children) == 3, 'Syntax error'
            assert isinstance(tree.child(0), ID) and \
                   isinstance(tree.child(1), Terminal) and tree.child(1).text == '=' and \
                   isinstance(tree.child(2), NonTerminal) and tree.child(2).type == 'Expr', 'Syntax error'
            value = tree.child(2).value
            tree.child(0).value = value
            var_table[tree.child(0).id] = value  # update var_table
        # Expr
        elif tree.type == 'Expr':
            '''expr : expr '+' term | expr '-' term | term'''
            assert len(tree.children) == 1 or len(tree.children) == 3, 'Syntax error'
            if len(tree.children) == 1:
                assert isinstance(tree.child(0), NonTerminal) and tree.child(0).type == 'Term', 'Syntax error'
                tree.value = tree.child(0).value
            elif len(tree.children) == 3:
                assert isinstance(tree.child(0), NonTerminal) and tree.child(0).type == 'Expr' and \
                       isinstance(tree.child(1), Terminal) and (tree.child(1).text in ('+', '-')) and \
                       isinstance(tree.child(2), NonTerminal) and tree.child(2).type == 'Term', 'Syntax error'
                op = tree.child(1).text
                if op == '+':
                    value = tree.child(0).value + tree.child(2).value
                else:
                    value = tree.child(0).value - tree.child(2).value
                tree.value = value
        # Term
        elif tree.type == 'Term':
            '''term : term '*' factor | term '/' factor | factor'''
            assert len(tree.children) == 1 or len(tree.children) == 3, 'Syntax error'
            if len(tree.children) == 1:
                assert isinstance(tree.child(0), NonTerminal) and tree.child(0).type == 'Factor', 'Syntax error'
                tree.value = tree.child(0).value
            elif len(tree.children) == 3:
                assert isinstance(tree.child(0), NonTerminal) and tree.child(0).type == 'Term' and \
                       isinstance(tree.child(1), Terminal) and (tree.child(1).text in ('*', '/')) and \
                       isinstance(tree.child(2), NonTerminal) and tree.child(2).type == 'Factor', 'Syntax error'
                op = tree.child(1).text
                if op == '*':
                    value = tree.child(0).value * tree.child(2).value
                else:
                    assert tree.child(2).value != 0, '除数不能为0'
                    value = tree.child(0).value / tree.child(2).value
                tree.value = value
        # Factor
        elif tree.type == 'Factor':
            """factor : ID | NUMBER | '(' expr ')'"""
            assert len(tree.children) == 1 or len(tree.children) == 3, 'Syntax error'
            if len(tree.children) == 1:
                assert isinstance(tree.child(0), ID) or isinstance(tree.child(0), Number), 'Syntax error'
                if isinstance(tree.child(0), ID):
                    value = var_table.get(tree.child(0).id)  # search for var_table
                    assert value is not None, f'符号 "{tree.child(0).id}" 未定义'
                    tree.child(0).value = value
                    tree.value = value
                else:
                    tree.value = tree.child(0).value
            elif len(tree.children) == 3:
                assert isinstance(tree.child(0), Terminal) and tree.child(0).text == '(' and \
                       isinstance(tree.child(1), NonTerminal) and tree.child(1).type == 'Expr' and \
                       isinstance(tree.child(2), Terminal) and tree.child(2).text == ')', 'Syntax error'
                tree.value = tree.child(1).value
        # Exprs
        elif tree.type == 'Exprs':
            """exprs : exprs ',' expr | expr"""
            assert len(tree.children) == 1 or len(tree.children) == 3, 'Syntax error'
            if len(tree.children) == 1:
                assert isinstance(tree.child(0), NonTerminal) and tree.child(0).type == 'Expr', 'Syntax error'
                tree.value = [tree.child(0).value]
            elif len(tree.children) == 3:
                assert isinstance(tree.child(0), NonTerminal) and tree.child(0).type == 'Exprs' and \
                       isinstance(tree.child(1), Terminal) and tree.child(1).text == ',' and \
                       isinstance(tree.child(2), NonTerminal) and tree.child(2).type == 'Expr', 'Syntax error'
                tree.value = tree.child(0).value + [tree.child(2).value]
        # Print
        elif tree.type == 'Print':
            ''' print : PRINT '(' exprs ')' | PRINT '(' ')' '''
            assert (len(tree.children) == 4 and
                    isinstance(tree.child(0), Terminal) and tree.child(0).text == 'print' and
                    isinstance(tree.child(1), Terminal) and tree.child(1).text == '(' and
                    isinstance(tree.child(2), NonTerminal) and tree.child(2).type == 'Exprs' and
                    isinstance(tree.child(3), Terminal) and tree.child(3).text == ')') or \
                   (len(tree.children) == 3 and
                    isinstance(tree.child(0), Terminal) and tree.child(0).text == 'print' and
                    isinstance(tree.child(1), Terminal) and tree.child(1).text == '(' and
                    isinstance(tree.child(2), Terminal) and tree.child(2).text == ')'), 'Syntax error'
            if len(tree.children) == 4:
                print(*tree.child(2).value)
            else:
                print()
