import re


class Rule:
    """
    产生式表示
    """

    def __init__(self, conditions: tuple, result: str, confidence: float = 1.0):
        assert -1.0 <= confidence <= 1.0, f'置信度 {confidence} 不在 [-1, 1] 的范围内'
        self.conditions: tuple = tuple(sorted(set(conditions)))
        self.result: str = result
        self.confidence: float = confidence
        self.used = False

    def __str__(self) -> str:
        return f"IF {' AND '.join(self.conditions)} THEN {self.result} [{self.confidence}]"

    @staticmethod
    def parse(string: str):
        """
        解析一个字符串为产生式（规则），形如：
        IF A AND B AND THEN D [置信度]
        """
        match = re.match(r'^IF\s*([^\d.]+)\s*THEN\s*([^\d.]+)\s*(\[-?\s*\d+\.?\d*\s*])?$', string.strip(),
                         flags=re.IGNORECASE)
        if not match:
            return None
        conditions_str = match.group(1)
        result = match.group(2).strip().split('是')[-1]
        if len(result) == 0:
            return None
        conditions = tuple(item.strip().split('是')[-1]
                           for item in re.split(r'\s*AND\s*', conditions_str, flags=re.IGNORECASE))
        if len(conditions) == 0:
            return None
        confidence = match.group(3)
        if confidence is not None:
            return Rule(conditions, result, float(confidence[1:-1]))
        return Rule(conditions, result)


class RuleBase:
    def __init__(self):
        self.rules: list = []
        self.__certainty: bool = True  # 判断是否全为确定性规则
        self.aims: set = set()  # 保存目标结论

    def read(self, rule_file: str, aim_file: str):
        with open(rule_file, 'r', encoding='utf-8') as file:
            self.rules = list(filter(lambda x: x is not None, map(Rule.parse, file.readlines())))
        self.__certainty = all(map(lambda x: x.confidence == 1.0, self.rules))
        with open(aim_file, 'r', encoding='utf-8') as file:
            self.aims = set(map(lambda x: x.strip().split('是')[-1], file.readlines()))

    def write(self, rule_file: str):
        with open(rule_file, 'w', encoding='utf-8') as file:
            for rule in self.rules:
                if self.__certainty:
                    file.write(f"IF {' AND '.join(rule.conditions)} THEN {rule.result}\n")
                else:
                    file.write(str(rule) + '\n')

    def add(self, string: str):
        rule = Rule.parse(string)
        if rule is None:
            return False
        self.rules.append(rule)
        return True

    def list(self) -> str:
        res = ''
        for index, rule in enumerate(self.rules):
            res += f'[{index}] {str(rule)}\n'
        return res

    def delete(self, index: int):
        assert 0 <= index < len(self.rules), '错误的索引'
        self.rules.pop(index)

    def all_used(self):
        return all(map(lambda x: x.used, self.rules))
