# -*- coding: utf-8 -*-
from ply import lex as lex
from ply import yacc as yacc

tokens = ('SYMBOL', 'COUNT',)

t_SYMBOL = r"C[laroudsemf]?|Os?|N[eaibdpos]?|S[icernbmg]?|P[drmtboau]?|" \
           r"H[eofgas]?|A[lrsgutcm]|B[eraik]?|Dy|E[urs]|F[erm]?|G[aed]|" \
           r"I[nr]?|Kr?|L[iaur]|M[gnodt]|R[buhenaf]|T[icebmalh]|" \
           r"U|V|W|Xe|Yb?|Z[nr]"
t_COUNT = r'\d+'


def t_newline(t):
    r"""\n+"""
    t.lexer.lineno += len(t.value)


t_ignore = ' \t'


# Error handling rule
def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)


lexer = lex.lex()


class Atom:
    def __init__(self, symbol: str, count: int):
        self.symbol = symbol
        self.count = count

    def __str__(self):
        return f'Atom({self.symbol}, {self.count})'


class Formula:
    def __init__(self):
        self.atom_count = 0
        self.atom_list = []

    def __add__(self, other: Atom):
        self.atom_count += other.count
        self.atom_list.append(other)
        return self

    def __str__(self):
        return f'Formula(atom_count={self.atom_count}, atom=[{", ".join(map(str, self.atom_list))}])'


'''
参考语法
species_list :  species_list species
species_list :  species
species :     SYMBOL
species :     SYMBOL COUNT
'''


def p_species_list_species_list_species(p):
    """species_list : species_list species"""
    p[0] = p[1] + p[2]


def p_species_list_species(p):
    """species_list : species"""
    p[0] = Formula() + p[1]


def p_species_sym_cnt(p):
    """species : SYMBOL COUNT"""
    p[0] = Atom(p[1], int(p[2]))


def p_species_sym(p):
    """species : SYMBOL"""
    p[0] = Atom(p[1], 1)


# Error rule for syntax errors
def p_error(p):
    print("Syntax error in input!")


parser = yacc.yacc()


def atom_count(formula: str):
    return parser.parse(formula)


if __name__ == '__main__':
    result = atom_count(input('请输入化学式: '))
    if result is None:
        print('未能成功解析')
    print('该化学式的原子数为: ', result.atom_count)
