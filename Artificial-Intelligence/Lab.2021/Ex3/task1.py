import math
import random

from genetic import Individual
from util import run


class Number(Individual):
    def __repr__(self):
        return 'Number({}, DNA={})'.format(Number.decoder(self.dna), self.dna.__repr__())

    def copy(self):
        return Number(self.dna)

    """
    编解码方法：
    A ~ B : encode() = A => B; decode() = B => A
    利用集合的等势：[0.0, 10.00] ~ [0, 1000] ~ [0.0, 1.0] ~ [0, 1023]
    第1处：encode(x) = int(100 * x); decode(x) = x / 100.0;
    第2处：encode(x) = x / 1000.0; decode(x) = int(1000 * x);
    第3处：encode(x) = int(1023 * x); decode(x) = x / 1023.0;
    therefore: [0.0, 10.00] ~ [0, 1023]
    encode(x) = int(1023 * int(100 * x) / 1000.0)
    decode(x) = int(1000 * x / 1023.0) / 100.0
    """
    CODE_LEN = 10

    @staticmethod
    def decoder(dna) -> float:
        def decode(x: int) -> float:
            return int(1000 * x / 1023.0) / 100.0

        if isinstance(dna, Number):
            dna = dna.dna
        assert len(dna) == Number.CODE_LEN
        return decode(int('0b' + dna, base=2))

    @staticmethod
    def encoder(code: float) -> str:
        def encode(x: float) -> int:
            return int(1023 * int(100 * x) / 1000.0)

        assert 0 <= code <= 10.0
        dna = bin(encode(code))[2:]
        if len(dna) < Number.CODE_LEN:  # 不足10位的补0
            dna = '0' * (Number.CODE_LEN - len(dna)) + dna
        return dna

    @staticmethod
    def random():
        code = random.uniform(0.0, 10.0)
        number = Number(Number.encoder(code))
        return number

    def cross_over(self, another, start=None, end=None):  # 交换
        """
        交叉互换，单点交叉或两点交叉。
        若只提供start，则单点交叉start..LEN；
        若只提供end，则单点交叉0..end；
        若都提供，则两点交叉min(start, end)..max(start, end)；
        若都不提供，则随机选择交叉点进行两点交叉。
        """
        if self.dna == another.dna:
            return self.copy()
        # 若未提供交叉点，则等概率地随机选择
        if start is None and end is None:
            start = random.randrange(0, Number.CODE_LEN)
            end = random.randrange(1, Number.CODE_LEN + 1)
        elif start is None:
            start = 0
        elif end is None:
            end = Number.CODE_LEN
        start, end = min(start, end), max(start, end)
        if start == end:
            end += 1
        assert 0 <= start < Number.CODE_LEN and 0 < end <= Number.CODE_LEN
        # 两点交叉
        new_self_dna = self.dna[:start] + another.dna[start:end] + self.dna[end:]
        new_num = Number(new_self_dna)
        return new_num

    def mutation(self, point=None):  # 变异
        if point is None:  # 若未提供变异点，则等概率地随机选择一个
            point = random.randrange(0, Number.CODE_LEN)
        else:
            assert 0 <= point < Number.CODE_LEN
        bit = self.dna[point]
        if bit == '0':
            bit = '1'
        else:
            bit = '0'
        return Number(self.dna[:point] + bit + self.dna[point + 1:])

    @staticmethod
    def fitness(x):
        return 10 * math.sin(5 * x) + 7 * abs(x - 5) + 10


if __name__ == '__main__':
    config = {
        'population_size': 15,
        'crossover_prob': 0.75,
        'mutation_prob': 0.1,
        'best_save_rate': 0.1,
        'decoder': Number.decoder,
        'encode_len': Number.CODE_LEN,
        'fit': Number.fitness,
        "crossover_type": 'double',
        'population_print_mode': 'each',
    }
    log_file_name = 'task1.out'
    epoch_list = (10, 20, 30)
    generator = Number.random
    rounds = 20
    run(rounds, epoch_list, generator, config, log_file_name,
        init_func=(lambda average: Number(Number.encoder(round(average, 2)))),
        fit_func=lambda individual: Number.fitness(Number.decoder(individual)))
