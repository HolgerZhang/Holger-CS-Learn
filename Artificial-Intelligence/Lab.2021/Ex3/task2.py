import random

from genetic import Individual
from util import run


class Schedule(Individual):
    artifact_number = None
    machine_number = None
    table = None

    @classmethod
    def set_property(cls, artifact_number, machine_number, tb):
        assert 0 < artifact_number == len(tb) and 0 < machine_number == len(tb[0])
        cls.artifact_number = artifact_number  # 工件数量
        cls.machine_number = machine_number  # 机器数量
        cls.table = [[0 for _ in range(machine_number + 1)]]  # 加工时间表
        for line in tb:
            cls.table.append([0] + line)

    def __init__(self, dna):
        super(Schedule, self).__init__(tuple(dna))

    def __repr__(self):
        return 'Schedule({})'.format('-'.join(map(str, self.dna)))

    def copy(self):
        return Schedule(self.dna)

    @staticmethod
    def decoder(dna) -> tuple:  # 实值编码，无需解码
        if isinstance(dna, Schedule):
            return dna.dna
        elif isinstance(dna, tuple):
            return dna
        return tuple(dna)

    @staticmethod
    def random():
        dna = list(range(1, Schedule.artifact_number + 1))
        random.shuffle(dna)
        return Schedule(dna)

    def cross_over(self, another, start=None, end=None):  # 交叉互换
        """
        交叉互换，使用次序交叉法。
        次序交叉法：随机地在双亲中选择两个交叉点，再交换杂交段，其他基因的位置根据双亲相应基因的相对位置确定。
        这样来保证产生的子代仍然是合法的，即染色体各位无重复无遗漏。
        若只提供start，则单点交叉start..LEN；
        若只提供end，则单点交叉0..end；
        若都提供，则两点交叉min(start, end)..max(start, end)；
        若都不提供，则随机选择两个交叉点。
        下面举例说明该算法：
        e.g. A = <0, 8, 5, 4, 7, 3, 1, 6, 9, 2>
             B = <1, 5, 4, 6, 9, 0, 3, 2, 8, 7>
             选择随机交叉点：start=4, end=8 交换杂交段：（ % 表示暂时留空）
            A' = <%, %, %, %,|9, 0, 3, 2,|%, %>
            B' = <%, %, %, %,|7, 3, 1, 6,|%, %>
            之后从 A 第二个杂交点后开始循环遍历整个染色体：
                  9  2  0  8  5  4  7  3  1  6
            去除杂交段的元素得到：
                           8  5  4  7     1  6
            从 A' 第二个杂交点后依次填入空位，得到子代：
            A' = <4, 7, 1, 6,|9, 0, 3, 2,|8, 5>
            同理可得：（这里默认只产生一个子代，故不返回 B'）
            B' = <4, 9, 0, 2,|7, 3, 1, 6,|8, 5>
        """
        if self.dna == another.dna:
            return self.copy()
        CODE_LEN = self.artifact_number
        # 若未提供交叉点，则等概率地随机选择
        if start is None and end is None:
            start = random.randrange(0, CODE_LEN)
            end = random.randrange(1, CODE_LEN + 1)
        elif start is None:
            start = 0
        elif end is None:
            end = CODE_LEN
        start, end = min(start, end), max(start, end)
        if start == end:
            end += 1
        assert 0 <= start < CODE_LEN and 0 < end <= CODE_LEN
        # 次序交叉法
        crossover = list(another.dna[start:end])
        new_self_dna = [None for _ in range(start)] + crossover + [None for _ in range(end, CODE_LEN)]
        tmp = self.dna[end:] + self.dna[:end]
        unused = list(filter(lambda x: x not in crossover, tmp))
        for i, v in zip(list(range(end, CODE_LEN)) + list(range(start)), unused):
            new_self_dna[i] = v
        new_num = Schedule(new_self_dna)
        return new_num

    def mutation(self, point=None):  # 变异: 与后一个数字交换
        if point is None:  # 若未提供变异点，则等概率地随机选择一个
            point = random.randrange(0, Schedule.artifact_number)
        else:
            assert 0 <= point < Schedule.artifact_number
        if point == Schedule.artifact_number - 1:
            another = point - 1
        else:
            another = point + 1
        dna = list(self.dna)
        dna[point], dna[another] = dna[another], dna[point]
        return Schedule(dna)

    @staticmethod
    def fitness(x):
        tmp = [[0 for _ in range(Schedule.machine_number + 1)] for _ in range(Schedule.artifact_number + 1)]
        for i in range(1, Schedule.artifact_number + 1):
            for j in range(1, Schedule.machine_number + 1):
                tmp[i][j] = max(tmp[i - 1][j], tmp[i][j - 1]) + Schedule.table[x[i - 1]][j]
        return tmp[-1][-1]


if __name__ == '__main__':
    Schedule.set_property(artifact_number=5, machine_number=4,
                          tb=[[31, 41, 25, 30],
                              [19, 55, 3, 34],
                              [23, 42, 27, 6],
                              [13, 22, 14, 13],
                              [33, 5, 57, 19]])
    config = {
        'population_size': 20,
        'crossover_prob': 0.6,
        'mutation_prob': 0.1,
        'best_save_rate': 0.1,
        'decoder': Schedule.decoder,
        'encode_len': Schedule.artifact_number,
        'fit': Schedule.fitness,
        "crossover_type": 'double',
        'population_print_mode': 'init',
        'minimize': True,
    }
    log_file_name = 'task2.out'
    epoch_list = (10, 20, 30)
    generator = Schedule.random
    rounds = 20
    run(rounds, epoch_list, generator, config, log_file_name)
