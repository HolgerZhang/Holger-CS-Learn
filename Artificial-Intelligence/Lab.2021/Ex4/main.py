import itertools


class Graph:
    best_value_map = {
        '1': (1, 1),
        '2': (1, 2),
        '3': (1, 3),
        '4': (2, 1),
        '5': (2, 2),
        '6': (2, 3),
        '7': (3, 1),
        '8': (3, 2),
        'x': (None, None),
    }

    def __init__(self, initialize: str, level=0):
        graph = initialize.strip().split()
        assert len(graph) == 9 and graph.count('x') == 1
        self._graph = [[None for _ in range(5)] for _ in range(5)]
        self._level = level
        self.x_positon = [None, None]
        for i, v in enumerate(graph):
            self._graph[i // 3 + 1][i % 3 + 1] = v
            if v == 'x':
                self.x_positon = [i // 3 + 1, i % 3 + 1]

    def clone(self):
        return Graph(str(self), self._level + 1)

    def __repr__(self):
        return '\n'.join(' '.join(x[1:-1]) for x in self._graph[1:-1])

    @property
    def value_list(self):
        lst = []
        for x in self._graph[1:-1]:
            lst.extend(x[1:-1])
        return lst

    def has_efficient_solution(self) -> bool:
        numbers = list(map(int, filter(lambda x: x != 'x', self.value_list)))
        reversed_count = 0
        for i, j in itertools.combinations(range(len(numbers)), 2):
            if i < j and numbers[i] > numbers[j]:
                reversed_count += 1
        return reversed_count % 2 == 0

    @property
    def h(self) -> int:
        manhattan = 0
        for i in range(1, 4):
            for j in range(1, 4):
                best_i, best_j = self.best_value_map[self._graph[i][j]]
                if best_i is None:
                    continue
                manhattan += abs(i - best_i) + abs(j - best_j)
        return manhattan

    @property
    def g(self) -> int:
        return self._level

    @property
    def f(self) -> int:
        return self.g + self.h

    def is_best_solution(self) -> bool:
        return self.h == 0

    def move(self):
        childern = []
        directions = ((0, 1), (1, 0), (0, -1), (-1, 0))
        for direction in directions:
            new_x_position = [self.x_positon[0] + direction[0], self.x_positon[1] + direction[1]]
            if self._graph[new_x_position[0]][new_x_position[1]] is None:  # 达到边界
                continue
            new_graph = self.clone()
            new_graph._graph[self.x_positon[0]][self.x_positon[1]], \
                new_graph._graph[new_x_position[0]][new_x_position[1]] = \
                new_graph._graph[new_x_position[0]][new_x_position[1]], \
                new_graph._graph[self.x_positon[0]][self.x_positon[1]]
            new_graph.x_positon = new_x_position
            childern.append(new_graph)
        return childern


def a_star():
    while True:
        inputs = input('请输入一个以空格隔开的字符串表示的3*3拼图（输入q退出）：')
        if inputs.strip() == 'q':
            return
        init_graph = Graph(inputs)
        if not init_graph.has_efficient_solution():
            print('无法搜到有效解')
            continue
        history = [init_graph]
        move_count = 0
        graph = init_graph
        while not graph.is_best_solution():
            next_graphs = graph.move()
            assert len(next_graphs) != 0
            graph = min(next_graphs, key=lambda g: g.f)
            move_count += 1
            history.append(graph)
        print('最少移动次数:', move_count)
        print('每一步的移动过程:')
        for i, g in enumerate(history):
            print('Step', i)
            print(g)
            print('-' * 6)


if __name__ == '__main__':
    a_star()
