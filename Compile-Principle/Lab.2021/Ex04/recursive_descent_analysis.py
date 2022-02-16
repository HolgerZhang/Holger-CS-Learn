"""
递归下降语法分析，文法：
E → TE'
E' → +TE' | e
T → F T'
T' → * F T' | e
F → (E) | id
样例输入：
id + id * id
"""
import sys


class AnalysisTree:
    # 分析树的前缀
    @staticmethod
    def prefix(name: str):
        return '[{name}'.format(name=name)

    # 分析树的后缀
    @staticmethod
    def suffix():
        return ']'


class RecursiveDescentAnalyser:
    # 终结符
    PLUS = '+'
    TIMES = '*'
    ID = 'id'
    LEFT = '('
    RIGHT = ')'
    FINISH = '$'
    EMPTY = 'e'
    # 非终结符
    NON_E = 'E'
    NON_E1 = "E'"
    NON_T = 'T'
    NON_T1 = "T'"
    NON_F = 'F'
    # 预测分析表
    PredictiveAnalysisTable = {
        NON_E: ((ID, LEFT),),
        NON_E1: ((PLUS,), (RIGHT, FINISH)),
        NON_T: ((ID, LEFT),),
        NON_T1: ((TIMES,), (PLUS, RIGHT, FINISH)),
        NON_F: ((ID,), (LEFT,))
    }

    def __init__(self, string: str):
        self._input = string.strip().split()
        if len(self._input) == 0 or self._input[-1] != self.FINISH:
            self._input.append(self.FINISH)
        self._tree = ''
        self._index = 0

    def analysis(self):
        err_flag = False
        if not self.production_E():
            print('Invalid Input at "{}"!'.format(self._input[self._index]), file=sys.stderr)
            err_flag = True
        result = self._tree if not err_flag else ''
        self._tree = ''
        self._index = 0
        return result

    def production_E(self):
        """ E → TE' """
        if self._input[self._index] in self.PredictiveAnalysisTable[self.NON_E][0]:
            self._tree += AnalysisTree.prefix(self.NON_E)
            if self.production_T() and self.production_E1():
                self._tree += AnalysisTree.suffix()
                return True
        return False

    def production_E1(self):
        """ E' → +TE' | e """
        # E' → +TE'
        if self._input[self._index] in self.PredictiveAnalysisTable[self.NON_E1][0]:
            self._tree += AnalysisTree.prefix(self.NON_E1)
            if self._input[self._index] == self.PLUS:
                self._tree += AnalysisTree.prefix(self.PLUS) + AnalysisTree.suffix()
                self._index += 1
            else:
                return False
            if self.production_T() and self.production_E1():
                self._tree += AnalysisTree.suffix()
                return True
        # E' → e
        elif self._input[self._index] in self.PredictiveAnalysisTable[self.NON_E1][1]:
            self._tree += AnalysisTree.prefix(self.NON_E1)
            self._tree += AnalysisTree.prefix(self.EMPTY) + AnalysisTree.suffix()
            self._tree += AnalysisTree.suffix()
            return True
        return False

    def production_T(self):
        """ T → F T' """
        if self._input[self._index] in self.PredictiveAnalysisTable[self.NON_T][0]:
            self._tree += AnalysisTree.prefix(self.NON_T)
            if self.production_F() and self.production_T1():
                self._tree += AnalysisTree.suffix()
                return True
        return False

    def production_T1(self):
        """ T' → * F T' | e """
        # T' → * F T'
        if self._input[self._index] in self.PredictiveAnalysisTable[self.NON_T1][0]:
            self._tree += AnalysisTree.prefix(self.NON_T1)
            if self._input[self._index] == self.TIMES:
                self._tree += AnalysisTree.prefix(self.TIMES) + AnalysisTree.suffix()
                self._index += 1
            else:
                return False
            if self.production_F() and self.production_T1():
                self._tree += AnalysisTree.suffix()
                return True
        # T' → e
        elif self._input[self._index] in self.PredictiveAnalysisTable[self.NON_T1][1]:
            self._tree += AnalysisTree.prefix(self.NON_T1)
            self._tree += AnalysisTree.prefix(self.EMPTY) + AnalysisTree.suffix()
            self._tree += AnalysisTree.suffix()
            return True
        return False

    def production_F(self):
        """ F → (E) | id """
        # F → id
        if self._input[self._index] in self.PredictiveAnalysisTable[self.NON_F][0]:
            self._tree += AnalysisTree.prefix(self.NON_F)
            if self._input[self._index] == self.ID:
                self._tree += AnalysisTree.prefix(self.ID) + AnalysisTree.suffix()
                self._index += 1
                self._tree += AnalysisTree.suffix()
                return True
        # F → (E)
        elif self._input[self._index] in self.PredictiveAnalysisTable[self.NON_F][1]:
            self._tree += AnalysisTree.prefix(self.NON_F)
            if self._input[self._index] == self.LEFT:
                self._tree += AnalysisTree.prefix(self.LEFT) + AnalysisTree.suffix()
                self._index += 1
            if not self.production_E():
                return False
            if self._input[self._index] == self.RIGHT:
                self._tree += AnalysisTree.prefix(self.RIGHT) + AnalysisTree.suffix()
                self._index += 1
                self._tree += AnalysisTree.suffix()
                return True
        return False


if __name__ == '__main__':
    analyser = RecursiveDescentAnalyser(input('Please input the lexical units: '))
    print(analyser.analysis())
