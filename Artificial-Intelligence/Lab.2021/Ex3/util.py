import sys

from prettytable import PrettyTable

from genetic import Genetic


class Printer:
    def __init__(self, fp=None):
        self.table = None
        self.out = fp if fp is not None else sys.stdout

    def add(self, **kwargs):
        if self.table is None:
            self.table = PrettyTable(kwargs)
        self.table.add_row(kwargs.values())

    def print(self):
        print(self.table, file=self.out)
        del self.table
        self.table = None


def run(rounds, epoch_list, generator, config, log_file_name, init_func=None, fit_func=None):
    log_file = open(log_file_name, 'w', encoding='utf-8')
    env = Genetic(**config)
    table = PrettyTable(['round', 'total_epoch', 'best', 'best_fitness', 'best_frequency', 'best_appearance', 'worst',
                         'worst_fitness'])
    for epoch in epoch_list:
        statistics = []
        for r in range(rounds):
            print(f'Round#{r}, epoch={epoch}'.center(50, '='), file=log_file)
            print('Initial'.center(50, '-'), file=log_file)
            env.init_population(generator, cb=Printer(fp=log_file))
            print('Process'.center(50, '-'), file=log_file)
            ret = env.construction(epoch=epoch, cb=Printer(fp=log_file))
            env.reset()
            table.add_row([r] + list(ret.values()))
            statistics.append(ret)
        evaluate(statistics, epoch, env.decoder, init_func, minimize=env.minimize, fit_func=fit_func)
    print('Statistics'.center(50, '='), file=log_file)
    print(table, file=log_file)
    log_file.close()


def evaluate(statistics, ep, decode_func, init_func=None, fit_func=None, minimize=False):
    if minimize:  # 是否进行最小化，默认最大化
        _max = min
        _min = max
    else:
        _max = max
        _min = min
    best = []
    for record in statistics:
        best.append(dict(individual=record['best'], fitness=record['best_fitness'], freq=record['best_frequency'],
                         epoch=record['best_appearance']))
    best_individual = _max(best, key=lambda x: x['fitness'])  # 最好解
    worst_individual = _min(best, key=lambda x: x['fitness'])  # 最坏解
    # 如果给定了 init_func ，则计算各个体解码后的平均值，再构造为新的个体，否则直接计算平均值
    if init_func:
        average = sum(decode_func(b['individual']) for b in best) / len(best)  # 平均解
        individual = init_func(average)
        avg_individual = (individual, round(fit_func(individual), 6))
    else:
        avg_individual = round(sum(b['fitness'] for b in best) / len(best), 6)  # 平均解
    best = list(filter(lambda x: best_individual['individual'] == x['individual'], best))
    best_freq = len(best) / len(statistics)  # 最好解频率
    best_avg_epoch = sum(b['epoch'] for b in best) / ep  # 最好解的平均迭代次数
    print(f'遗传算法运行结果（迭代轮次 Epoch={ep} ）')
    table = PrettyTable(['Rounds', 'Best', 'Worst', 'Average', 'Frequency (Best)', 'Average Epoch (Best)'])
    table.add_row([len(statistics), (best_individual['individual'], round(best_individual['fitness'], 6)),
                   (worst_individual['individual'], round(worst_individual['fitness'], 6)),
                   avg_individual, best_freq, round(best_avg_epoch, 6)])
    print(table)
