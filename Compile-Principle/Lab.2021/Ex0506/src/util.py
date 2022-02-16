class TableItem:
    """
    预测分析表项
    """

    GOTO = 'goto'  # 转移
    SHIFT = 's'  # 移进
    REDUCE = 'r'  # 规约
    ACCEPT = 'acc'  # 接受

    def __init__(self):
        self.actions = set()

    def add(self, action: str, i: int):
        """
        添加一项
        :param action: 动作 | GOTO
        :param i: 标号
        """
        assert action in (TableItem.SHIFT, TableItem.REDUCE, TableItem.ACCEPT, TableItem.GOTO) and isinstance(i, int)
        self.actions.add((action, i))

    def get_actions(self):
        """
        获取所有动作
        """
        result = {}
        for action, i in self.actions:
            result.setdefault(action, set()).add(i)
        return result

    def is_empty_action(self):
        """
        是否为空表项
        """
        return len(self.actions) == 0

    def exist_conflict(self):
        """
        是否存在冲突
        """
        return (not self.is_empty_action()) and len(self.actions) != 1

    def which_conflict(self):
        """
        是哪种冲突
        """
        return 'reduce-reduce' if len(self.get_actions()[TableItem.REDUCE]) > 1 else 'shift-reduce'

    def is_accept(self):
        """
        是否为接受状态
        """
        return self.actions.copy().pop()[0] == TableItem.ACCEPT

    def single_action(self):
        """
        获取单一的动作与标号
        """
        assert len(self.actions) == 1
        return self.actions.copy().pop()


class SymTree:
    """
    用字符串表示的语法树
    """

    def __init__(self):
        self.__tree_string = ''
        self.__sub_trees = []
        self.__last_head = ''

    @property
    def tree_string(self):
        return self.__tree_string

    def apply(self, head, body):
        """
        应用产生式
        :param head: 产生式首部
        :param body: 产生式尾部
        """
        if self.__last_head == ''.join(body):
            self.__tree_string = f'[{head} {self.__tree_string}]'
        elif len(body) > 1 and body[0] == '(' and self.__last_head == body[1] and body[2] == ')':
            already = self.__tree_string
            self.__tree_string = f'[{head} ( {self.__tree_string} )]'
            for i in range(len(self.__sub_trees) - 1, -1, -1):
                if already == self.__sub_trees[i]:
                    self.__sub_trees[i] = self.__tree_string
                    break
        else:
            if self.__tree_string:
                self.__sub_trees.append(self.__tree_string)
            if len(body) == 1:
                self.__tree_string = f'[{head} [{" ".join(body)}]]'
            else:
                self.__tree_string = f'[{head} {self.__sub_trees[-2]} {body[1]} {self.__sub_trees[-1]}]'
                self.__sub_trees = self.__sub_trees[:-2]
        self.__last_head = head
