from copy import deepcopy

from util import TableItem, SymTree


class Grammar:
    """
    文法类
    """
    EMPTY = 'e'  # 空状态

    def __init__(self, grammar_string: str):
        self.grammar = {}
        self.start = None
        self.terminals = set()
        self.non_terminals = set()
        self.symbols = set()
        self.add_grammar(grammar_string)

    def clear_grammar(self):
        """
        重置文法
        """
        self.grammar.clear()
        self.start = None
        self.terminals.clear()
        self.non_terminals.clear()
        self.symbols.clear()

    def add_grammar(self, grammar_string: str):
        """
        添加文法
        :param grammar_string: 形如 A -> a 的文法字符串
        """
        for production in filter(lambda x: x is not None and x.find('->') != -1, grammar_string.splitlines()):
            head, _, bodies = production.partition('->')
            head = head.strip()
            bodies = bodies.strip()
            if not head.isupper():
                raise ValueError(f"产生式 '{production}' 中不能认为 '{head}' 为非终结符!")
            if not self.start:
                self.start = head
            self.grammar.setdefault(head, set())
            self.non_terminals.add(head)
            for body in map(lambda x: tuple(x.split()), ' '.join(bodies.split()).split('|')):
                if Grammar.EMPTY in body and body != (Grammar.EMPTY,):
                    raise ValueError(f"产生式 '{production}' 中不允许使用空 '{Grammar.EMPTY}' ！")
                self.grammar[head].add(body)
                for symbol in body:
                    if symbol.isupper() and symbol != Grammar.EMPTY:
                        self.non_terminals.add(symbol)
                    else:
                        self.terminals.add(symbol)
        self.symbols = self.terminals | self.non_terminals

    def convert_extension_grammar(self):
        """
        转换为增广文法
        :return: 增广文法
        """
        extension_grammar = Grammar('')
        if self.start is None:
            return extension_grammar
        extension_grammar.start = f"{self.start}'"
        extension_grammar.grammar = deepcopy(self.grammar)
        extension_grammar.grammar[extension_grammar.start] = {(self.start,)}
        extension_grammar.terminals = deepcopy(self.terminals)
        extension_grammar.non_terminals = deepcopy(self.non_terminals)
        extension_grammar.non_terminals.add(extension_grammar.start)
        extension_grammar.symbols = extension_grammar.terminals | extension_grammar.non_terminals
        return extension_grammar


class SLR:
    """
    SLR (1) 语法分析器
    """
    DOT = '.'
    END = '$'

    def __init__(self, grammar: Grammar):
        self.extension_grammar = grammar.convert_extension_grammar()  # 增广文法
        self.grammar_indexed = []  # 为文法提供数值索引
        for head, bodies in self.extension_grammar.grammar.items():
            for body in bodies:
                self.grammar_indexed.append([head, body])
        self.FIRST, self.FOLLOW = self.FIRST_FOLLOW(self.extension_grammar)
        self.C = self.items_set_family(self.extension_grammar)  # 规范 LR(0) 项集族
        self.symbols = list(self.extension_grammar.terminals) + [SLR.END] + \
                       list(self.extension_grammar.non_terminals - {self.extension_grammar.start})
        self.table = self.analysis_table()  # 预测分析表

    @staticmethod
    def FIRST_FOLLOW(grammar: Grammar):
        """
        计算 FIRST 和 FOLLOW
        :param grammar: 增广文法
        :return: FIRST 和 FOLLOW 的 字典
        """
        FIRST = {symbol: set() for symbol in grammar.symbols}
        for terminal in grammar.terminals:
            FIRST[terminal] = {terminal}
        FOLLOW = {symbol: set() for symbol in grammar.non_terminals}
        FOLLOW[grammar.start].add(SLR.END)
        while True:
            updated = False
            for head, bodies in grammar.grammar.items():
                for body in bodies:
                    for symbol in body:
                        if symbol != Grammar.EMPTY:
                            before_updated_size = len(FIRST[head])
                            FIRST[head] |= FIRST[symbol] - {Grammar.EMPTY}
                            updated = before_updated_size != len(FIRST[head]) or updated
                            if Grammar.EMPTY not in FIRST[symbol]:
                                break
                        else:
                            before_updated_size = len(FIRST[head])
                            FIRST[head] |= {Grammar.EMPTY}
                            updated = before_updated_size != len(FIRST[head]) or updated
                    else:
                        before_updated_size = len(FIRST[head])
                        FIRST[head] |= {Grammar.EMPTY}
                        updated = before_updated_size != len(FIRST[head]) or updated
                    aux = FOLLOW[head]
                    for symbol in reversed(body):
                        if symbol == Grammar.EMPTY:
                            continue
                        if symbol in FOLLOW:
                            before_updated_size = len(FOLLOW[symbol])
                            FOLLOW[symbol] |= aux - {Grammar.EMPTY}
                            updated = before_updated_size != len(FOLLOW[symbol]) or updated
                        if Grammar.EMPTY in FIRST[symbol]:
                            aux = aux | FIRST[symbol]
                        else:
                            aux = FIRST[symbol]
            if not updated:
                return FIRST, FOLLOW

    def CLOSURE(self, I):
        """
        项集的闭包
        :param I: 项集
        :return: 闭包
        """
        closure = I  # I 中的各项加入闭包
        while True:
            old_size = len(closure)
            for head, bodies in closure.copy().items():
                for body in bodies.copy():
                    # 若 A -> a.Bb 在闭包中，B -> c 为产生式，将 B -> .c 加入闭包
                    if SLR.DOT in body[:-1]:
                        B = body[body.index(SLR.DOT) + 1]
                        if B in self.extension_grammar.non_terminals:
                            for c in self.extension_grammar.grammar[B]:  # B -> c 为产生式
                                closure.setdefault(B, set())
                                new_item = (SLR.DOT,) if c == (Grammar.EMPTY,) else (SLR.DOT,) + c
                                closure[B].add(new_item)
            if old_size == len(closure):  # 不断应用这一规则，直到没有新项可以加入闭包
                break
        return closure

    def GOTO(self, I, X):
        """
        GOTO 函数
        :param I: 项集
        :param X: 文法符号
        :return:
        """
        goto = {}
        for head, bodies in I.items():
            for body in bodies:
                # 若 A -> a.Xb 在 I 中，则 GOTO(I, X) 为形如 A -> aX.b 的项集的闭包
                if SLR.DOT in body[:-1]:
                    dot_pos = body.index(SLR.DOT)
                    if body[dot_pos + 1] == X:
                        replaced_dot_body = body[:dot_pos] + (X, SLR.DOT) + body[dot_pos + 2:]
                        for closure_head, closure_bodies in self.CLOSURE({head: {replaced_dot_body}}).items():
                            goto.setdefault(closure_head, set())
                            goto[closure_head].update(closure_bodies)
        return goto

    def items_set_family(self, grammar: Grammar):
        """
        构造一个增广文法 grammar 的规范 LR(0) 项集族
        :param grammar: 增广文法
        :return: 规范 LR(0) 项集族
        """
        C = [self.CLOSURE({grammar.start: {(SLR.DOT, grammar.start[:-1])}})]  # 规范 LR(0) 项集族
        while True:
            old_size = len(C)
            for I in C.copy():  # 项集 I
                for X in grammar.symbols:  # 文法符号 X
                    goto = self.GOTO(I, X)
                    if len(goto) != 0 and goto not in C:
                        C.append(goto)
            if old_size == len(C):  # 重复，直到在某轮没有新项加入 C
                break
        return C

    def analysis_table(self):
        """
        构造 SLR(1) 语法分析表
        :return: 构造 SLR(1) 语法分析表
        """
        # C 为增广文法的规范 LR(0) 项集族
        table = {s: {sym: TableItem() for sym in self.symbols} for s in range(len(self.C))}
        for index, I in enumerate(self.C):
            for head, bodies in I.items():
                for body in bodies:
                    if SLR.DOT in body[:-1]:  # 若 [A -> alpha . a beta] in I, GOTO(I, a) = I_j
                        a = body[body.index(SLR.DOT) + 1]
                        # 且 a 是终结符
                        if a in self.extension_grammar.terminals:
                            j = self.C.index(self.GOTO(I, a))
                            table[index][a].add(TableItem.SHIFT, j)  # 移进 j
                    elif body[-1] == SLR.DOT and head != self.extension_grammar.start:  # 若 [A -> alpha .] in I, A != S'
                        for j, (G_head, G_body) in enumerate(self.grammar_indexed):
                            if G_head == head and (G_body == body[:-1] or
                                                   G_body == (Grammar.EMPTY,) and body == (SLR.DOT,)):
                                # for all a in FOLLOW(A)
                                for a in self.FOLLOW[head]:
                                    table[index][a].add(TableItem.REDUCE, j)
                                break
                    else:  # 若 [A -> alpha .] in I, A = S'
                        table[index][SLR.END].add(TableItem.ACCEPT, 0)

            for A in self.extension_grammar.non_terminals:  # 对于非终结符，构造 GOTO
                j = self.GOTO(I, A)
                if j in self.C:
                    table[index][A].add(TableItem.GOTO, self.C.index(j))
        return table

    def parser(self, input_string):
        """
        基于预测分析表结合栈进行语法解析
        :param input_string: 输入串
        :return: 语法树（字符串）
        """
        buffer = f'{input_string} {SLR.END}'.split()  # 输入缓冲区
        forward = 0  # 向前看指针
        a = buffer[forward]  # 当前输入
        status_stack = [0]  # 状态栈
        tree = SymTree()

        step = 0
        while True:
            s = status_stack[-1]
            step += 1
            # print(s)
            if a not in self.table[s]:
                raise ValueError(f"未知的符号 '{a}'")
            elif self.table[s][a].is_empty_action():
                raise ValueError('给定的文法无法使用 SLR(1) 语法分析解析当前输入!')
            elif self.table[s][a].exist_conflict():
                raise ValueError(f"在状态{s}, 符号 '{a}' 存在 {self.table[s][a].which_conflict()} 冲突!")
            elif self.table[s][a].is_accept():
                break
            else:
                action, i = self.table[s][a].single_action()
                # print(action, i)
                if action == TableItem.SHIFT:  # 移进
                    status_stack.append(i)
                    forward += 1
                    a = buffer[forward]
                    pass
                elif action == TableItem.REDUCE:  # 规约
                    head, body = self.grammar_indexed[i]
                    tree.apply(head, body)  # 应用相应产生式
                    if body != (Grammar.EMPTY,):
                        status_stack = status_stack[:-len(body)]
                    _, s = self.table[status_stack[-1]][head].single_action()
                    status_stack.append(s)
        return tree.tree_string
