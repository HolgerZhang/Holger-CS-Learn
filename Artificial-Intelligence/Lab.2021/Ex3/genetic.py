import abc
import math
import random
import sys
from collections import Counter
from copy import deepcopy

from prettytable import PrettyTable


class Individual(abc.ABC):
    def __init__(self, dna):
        self.dna = dna

    def __eq__(self, other):
        return self.dna == other.dna

    def __hash__(self):
        return self.dna.__hash__()

    def __repr__(self):
        return 'Individual(DNA={})'.format(self.dna.__repr__())

    @abc.abstractmethod
    def copy(self):  # 复制个体
        pass

    @abc.abstractmethod
    def cross_over(self, another, start=None, end=None):  # 交叉互换
        """
        交叉互换。
        若只提供start，则单点交叉start..LEN；
        若只提供end，则单点交叉0..end；
        若都提供，则两点交叉min(start, end)..max(start, end)；
        若都不提供，则随机选择交叉点进行两点交叉。
        """
        pass

    @abc.abstractmethod
    def mutation(self, point=None):  # 变异
        pass


class Genetic:
    def __init__(self, population_size, decoder, encode_len, fit,
                 crossover_prob=0.5, mutation_prob=0.01, best_save_rate=0.1, minimize=False, **cfg):
        self.population = []  # 种群
        self.population_size = population_size  # 种群大小
        self.crossover_prob = crossover_prob  # 交叉互换概率
        self.mutation_prob = mutation_prob  # 变异概率
        self.save_num = math.ceil(self.population_size * best_save_rate)  # 最佳个体保留个数
        self.decoder = decoder  # 解码器
        self.fit = fit  # 适应度计算函数
        self.encode_len = encode_len  # 编码长度
        self.history = {}  # 保存历史 {epoch: {'best': x, 'worst': x, 'best_count': n, 'population': []}}
        self.cfg = cfg
        self.population_print_mode = self.cfg.get('population_print_mode', 'init').lower()  # init, each, none
        self.minimize = minimize  # 是否进行最小化，默认最大化
        if minimize:
            self._min = max
            self._max = min
        else:
            self._min = min
            self._max = max

    def init_population(self, generator, cb=None, size=None):  # 初始化种群
        self.population = []
        if size is None:
            size = self.population_size
        else:
            self.population_size = size
        for _ in range(size):
            self.population.append(generator())
        ret = self._eval_this_epoch(0)
        if cb is not None:
            cb.add(**ret)
            cb.print()
        if self.population_print_mode in ('init', 'each'):
            self._print_population(self.population, '[Initialize Population]', cb=cb)

    def _print_population(self, population, title=None, cb=None):
        table = PrettyTable(['Index', 'Individual', 'Fitness'])
        for i, p in enumerate(population):
            table.add_row([i, p, round(self.fit(self.decoder(p)), 6)])
        if title is not None:
            print(title, file=cb.out if cb is not None else sys.stdout)
        print(table, file=cb.out if cb is not None else sys.stdout)

    @staticmethod
    def _random_decision(prob):
        assert 0 <= prob <= 1
        if prob == 0:
            return False
        if prob == 1:
            return True
        return random.random() < prob

    def _do_select(self):  # 选择
        # 轮盘赌法和最佳个体保存方法相结合的选择
        selected = []
        fitness = [self.fit(self.decoder(item)) for item in self.population]
        best = self._max(self.population, key=lambda p: self.fit(self.decoder(p)))  # 最佳个体
        for _ in range(self.save_num):
            selected.append(copy(best))
        selected.extend(map(copy, random.choices(self.population, weights=fitness,
                                                 k=self.population_size - self.save_num)))
        return selected

    def _do_cross_over(self, population):  # 交叉
        selected = population[:]
        if self.population_size <= 1:
            return selected
        for index in range(self.save_num, self.population_size):  # 保留下来的最佳个体不会被交叉替换
            if not Genetic._random_decision(self.crossover_prob):
                continue
            while True:
                mother_index = random.randrange(0, self.population_size)
                if index != mother_index:
                    break
            # 交叉类型：double 两点交叉，simple 单点右侧交叉，reversed_simple 单点左侧交叉
            cross_over_type = self.cfg.get('crossover_type', 'double')
            if cross_over_type == 'double':
                st = random.randrange(0, self.encode_len)
                ed = random.randrange(1, self.encode_len + 1)
                selected[index] = population[index].cross_over(population[mother_index], start=st, end=ed)
            elif cross_over_type == 'simple':
                point = random.randrange(0, self.encode_len)
                selected[index] = population[index].cross_over(population[mother_index], start=point)
            elif cross_over_type == 'reversed_simple':
                point = random.randrange(0, self.encode_len)
                selected[index] = population[index].cross_over(population[mother_index], end=point)
            else:
                raise RuntimeError('Unsupported crossover type!')
        return selected

    def _do_mutation(self, population):  # 变异
        selected = population[:]
        for i in range(self.save_num, self.population_size):  # 保留下来的最佳个体不会变异
            if Genetic._random_decision(self.mutation_prob):
                point = random.randrange(0, self.encode_len)
                selected[i] = population[i].mutation(point=point)
        return selected

    def _eval_this_epoch(self, epoch: int):  # 评估当前epoch
        population = Counter(self.population)
        best = self._max(population.keys(), key=lambda p: self.fit(self.decoder(p)))
        best_item = (best, round(self.fit(self.decoder(best)), 6))
        worst = self._min(population.keys(), key=lambda p: self.fit(self.decoder(p)))
        worst_item = (worst, round(self.fit(self.decoder(worst)), 6))
        max_count = population[best]
        # {epoch: {'best': x, 'worst': x, 'average': x, 'best_count': n, 'population': []}}
        self.history[epoch] = dict(best=best_item, best_count=max_count, worst=worst_item,
                                   population=self.population)
        return dict(best=best_item, best_count=max_count, worst=worst_item)

    def construction(self, epoch: int, cb=None):  # 构建环境
        assert self.population_size == len(self.population), "default population not initialize"
        start = max(self.history.keys())
        for i in range(1, epoch + 1):
            next_population = self._do_select()
            next_population = self._do_cross_over(next_population)
            self.population = self._do_mutation(next_population)
            ep = start + i
            ret = self._eval_this_epoch(ep)
            if cb is not None:
                cb.add(**ret, epoch=ep)
            if self.population_print_mode == 'each':
                self._print_population(self.population, f'[Epoch {ep} Population]', cb=cb)
        if cb is not None:
            cb.print()
        if self.population_print_mode == 'init':
            self._print_population(self.population, '[Final Population]', cb=cb)
        return self.statistics()  # 统计末代种群

    def statistics(self):
        epoch = max(self.history.keys())
        final = self.history[epoch]
        best, best_fit = final['best']
        worst, worst_fit = final['worst']
        best_freq = round(final['best_count'] / self.population_size, 6)
        which_epoch = epoch
        for e, data in self.history.items():
            if data['best'][0] == best:
                which_epoch = e
                break
        return dict(total_epoch=epoch,
                    best=best, best_fitness=best_fit, best_frequency=best_freq, best_appearance=which_epoch,
                    worst=worst, worst_fitness=worst_fit)

    def reset(self):
        self.history = {}
        self.population = []


def copy(obj):
    if hasattr(obj, 'copy'):
        return obj.copy()
    return deepcopy(obj)
