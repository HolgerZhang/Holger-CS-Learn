# coding=utf-8
class _node:
    """
    所有节点的基类
    """
    def __init__(self, data):
        self._data = data
        self._children = []
        self._value = None

    @property
    def value(self):
        return self._value

    @value.setter
    def value(self, value):
        self._value = value

    def child(self, i):
        assert -len(self._children) <= i < len(self._children)
        return self._children[i]

    @property
    def children(self):
        return self._children

    def add(self, node):
        self._children.append(node)


class NonTerminal(_node):
    """
    非终结符节点，提供type表示非终结符的类型，value（可选）为值
    """
    @property
    def type(self):
        return self._data

    def __str__(self):
        if len(self.children) == 0:
            children = ''
        else:
            children = ' ' + ' '.join(map(str, self.children))
        if self._value is not None:
            val = str(self._value).replace(' ', '').replace('[', '<').replace(']', '>')
            return f"[{self.type}(value={val}){children}]"
        else:
            return f"[{self.type}{children}]"


class Number(_node):
    """
    数字节点，value为值
    """
    def __init__(self, data):
        super(Number, self).__init__(data)
        self._data = 'number'
        self._value = float(data)

    def __str__(self):
        return f'[{self._value}]'


class ID(_node):
    """
    标识符节点，提供id表示标识符名称，value为值
    """
    @property
    def id(self):
        return self._data

    def __init__(self, data):
        super(ID, self).__init__(data)
        self._value = 0.0

    def __str__(self):
        id_ = self._data
        val = self._value
        return f"[{id_}(value={val})]"


class Terminal(_node):
    """
    除标识符以外的终结符节点，提供text表示其内容
    """
    @property
    def text(self):
        return self._data

    def __str__(self):
        return f'[{self._data}]'
