from fuzzywuzzy import fuzz


class Fact:
    def __init__(self, name: str, confidence: float = 1.0):
        assert -1.0 <= confidence <= 1.0, f'置信度 {confidence} 不在 [-1, 1] 的范围内'
        self.name: str = name.strip().split('是')[-1]  # 只保留 'A是B' 的 B
        self.confidence: float = confidence

    def __str__(self) -> str:
        return f'{self.name} ({self.confidence})'

    @staticmethod
    def parse(string: str):
        items = string.strip().split()
        if len(items) == 1:
            return Fact(items[0])
        elif len(items) == 2:
            return Fact(items[0], float(items[1]))
        return None


class Database:
    def __init__(self):
        self.data: list = []
        self.starts: set = set()  # 避免推理得到输入的事实

    def read(self, basic_file: str):
        with open(basic_file, 'r', encoding='utf-8') as file:
            self.data = list(filter(lambda x: x is not None, map(Fact.parse, file.readlines())))
        self.starts = {fact.name.split('是')[-1] for fact in self.data}

    def write(self, fact_file: str):
        certainty = all(map(lambda x: x.confidence == 1.0, self.data))
        with open(fact_file, 'w', encoding='utf-8') as file:
            for fact in self.data:
                if certainty:
                    file.write(fact.name + '\n')
                else:
                    file.write(f'{fact.name} {fact.confidence}\n')

    def get(self, fact):
        target: str = fact.name if isinstance(fact, Fact) else str(fact)
        for f in self.data:
            if self.fuzzy_name_match(f.name, target):
                return f
        return None

    @staticmethod
    def fuzzy_name_match(name1: str, name2: str) -> bool:
        return fuzz.partial_ratio(name1, name2) >= 90

    def add(self, fact):
        new_fact = False
        if not isinstance(fact, Fact):
            fact = Fact(str(fact), 0.0)
            new_fact = True
        inserted = False
        exist = self.get(fact)
        if exist is not None:
            exist.confidence = self.synthesis(fact.confidence, exist.confidence)
            inserted = True
        if not inserted:
            if new_fact:
                fact.confidence = 1.0
            self.data.append(fact)

    @staticmethod
    def synthesis(cf1: float, cf2: float) -> float:
        if cf1 >= 0 and cf2 >= 0:
            cf12 = cf1 + cf2 - cf1 * cf2
        elif cf1 < 0 and cf2 < 0:
            cf12 = cf1 + cf2 + cf1 * cf2
        else:
            cf12 = (cf1 + cf2) / (1 - min(abs(cf1), abs(cf2)))
        return cf12

    def delete(self, index):
        assert 0 <= index < len(self.data), '错误的索引'
        self.data.pop(index)
