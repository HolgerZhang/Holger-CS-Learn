import json
import sys

from easydict import EasyDict


class PCFGParser:
    def __init__(self, config_file: str):
        self.__rules, self.__non_terminals, self.__start_symbol = self.__load_grammar(config_file)
        self._best_path_map = [[{}]]
        self._probability = None

    @staticmethod
    def __load_grammar(json_file: str):
        def read_grammar(file_name: str) -> dict:
            rules = {}
            with open(file_name, 'r', encoding='utf-8') as file:
                for line in file.readlines():
                    head, body = map(lambda s: s.strip(), line.strip().split('->'))
                    body = list(map(lambda s: s.strip(), body.split()))
                    probability = float(body[-1])
                    body = tuple(body[:-1]) if len(body) > 2 else body[0]
                    rules.setdefault(head, {})
                    rules[head][body] = probability
            return rules

        cfg = EasyDict(json.load(open(json_file, 'r', encoding='utf-8')))
        _rules = read_grammar(cfg.grammar_file)
        return _rules, set(cfg.non_terminals), cfg.start_symbol.strip()

    def set_sentence(self, sentences: str):
        word_list = sentences.strip().split()
        self._best_path_map = [[{non_terminal: dict(probability=0.0, path=dict(split=None, rule=None))
                                 for non_terminal in self.__non_terminals}
                                for _ in range(len(word_list))]
                               for _ in range(len(word_list))]
        # 填叶结点，计算得到每个单词所有语法组成的概率
        for i in range(len(word_list)):
            for non_terminal in self.__non_terminals:  # 遍历非终端符，找到并计算此条非终端-终端语法的概率
                if word_list[i] in self.__rules[non_terminal]:
                    self._best_path_map[i][i][non_terminal]['probability'] = self.__rules[non_terminal][word_list[i]]
                    self._best_path_map[i][i][non_terminal]['path'] = dict(split=None, rule=word_list[i])
                    for another_non_terminal in self.__non_terminals:
                        if non_terminal in self.__rules[another_non_terminal].keys():
                            self._best_path_map[i][i][another_non_terminal]['probability'] = \
                                self.__rules[non_terminal][word_list[i]] * \
                                self.__rules[another_non_terminal][non_terminal]
                            self._best_path_map[i][i][another_non_terminal]['path'] = dict(split=i, rule=non_terminal)
        for level in range(1, len(word_list)):
            for i in range(len(word_list) - level):  # 第一层
                j = i + level  # 第二层结点
                for non_terminal in self.__non_terminals:  # 获取每个非终端符
                    local_best = dict(probability=0, path=None)
                    for key, value in self.__rules[non_terminal].items():  # 遍历该非终端符所有语法规则
                        if key[0] not in self.__non_terminals:
                            break
                        for k in range(i, j):
                            # 计算产生的分裂点概率，保留最大概率
                            probability = 0 if len(key) != 2 else \
                                value * self._best_path_map[i][k][key[0]]['probability'] * \
                                self._best_path_map[k + 1][j][key[1]]['probability']
                            if probability > local_best['probability']:
                                local_best['probability'] = probability
                                local_best['path'] = dict(split=k, rule=key)  # 分裂点和生成的可用规则
                    self._best_path_map[i][j][non_terminal] = local_best  # 得到一个规则中最大概率

    def make_tree(self, left, right, root=None, index=0):
        if root is None:
            root = self.__start_symbol
        node = self._best_path_map[left][right][root]
        if root == self.__start_symbol:
            self._probability = node['probability']
        if node['path']['split'] is not None:  # 存在分裂点
            child = []
            if len(node['path']['rule']) == 2:  # 如果二元规则，递归调用左子树、右子树
                child.append(self.make_tree(left, node['path']['split'], node['path']['rule'][0], index + 1))
                child.append(self.make_tree(node['path']['split'] + 1, right, node['path']['rule'][1], index + 1))
            else:  # 否则只递归左子树
                child.append(self.make_tree(left, node['path']['split'], node['path']['rule'][0], index + 1))
            return f"[{root} {' '.join(child)}]"
        else:
            return f"[{root}[{node['path']['rule']}]]"

    @property
    def probability(self):
        return self._probability


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Error usage!')
        exit(0)
    parser = PCFGParser(sys.argv[-1])
    sentence = input()
    parser.set_sentence(sentence)
    print("句子:", sentence)
    print("最优分析树:", parser.make_tree(0, 3))
    print("最优分析树的概率: %g" % parser.probability)
