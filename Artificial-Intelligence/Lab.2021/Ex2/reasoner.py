from copy import deepcopy

from integrated_database import Database, Fact
from rule_base import RuleBase


class Reasoner:
    def __init__(self, rules: RuleBase, facts: Database):
        self.rules: RuleBase = rules
        self.facts: Database = facts
        self.__old_facts: Database = Database()

    def reasoning(self):
        while True:
            if self.rules.all_used():  # 所有产生式都使用了
                break
            self.__old_facts = deepcopy(self.facts)
            result = self.get_result()
            if result is not None:  # 数据库中已有结论
                print(f'数据库中已有结论：{result}，匹配成功')
                return result
            for i, rule in enumerate(self.rules.rules):
                if rule.used:
                    continue
                head = [self.facts.get(name) for name in rule.conditions]
                if any(map(lambda x: x is None, head)):
                    # print('no', i, rule, head)  # DEBUG
                    continue
                print(f'数据库中存在如下结论：', ', '.join(map(str, head)))
                print(f'使用产生式：{rule}')
                # 计算不确定度
                e_confidence = min(map(lambda x: x.confidence, head))
                cf_h = rule.confidence * max(0, e_confidence)
                new_fact = Fact(rule.result, cf_h)
                print(f'将新的证据 {new_fact} 加入综合数据库')
                self.facts.add(new_fact)
                rule.used = True
            if not self.facts_changed():  # 数据库没有变化
                break
        print('循环结束')
        result = self.get_result(need_mid=True)
        if result is not None:
            print(f'数据库中已有结论：{result}，匹配成功')
            return result
        else:
            print('未能匹配到任何一个结论')
            return None

    def get_result(self, need_mid=False):  # 拿到结论
        now_list = self.facts.data[:]
        now_list.sort(key=lambda x: x.confidence)
        print('当前综合数据库:', ', '.join(map(str, now_list)))
        for fact in reversed(now_list):
            # 综合数据库中存在事实
            if fact.name in self.rules.aims:
                return fact
        if need_mid:
            for fact in reversed(now_list):
                # 不存在事实，但是有中间结论
                if fact.name not in self.facts.starts:
                    return fact
        return None

    def facts_changed(self) -> bool:  # 判断数据库是否变化
        now_list = self.facts.data[:]
        old_list = self.__old_facts.data[:]
        if len(now_list) != len(old_list):
            print('综合数据库已改变')
            return True
        now_list.sort(key=lambda x: (x.name, x.confidence))
        old_list.sort(key=lambda x: (x.name, x.confidence))
        for now, old in zip(now_list, old_list):
            if not (Database.fuzzy_name_match(now.name, old.name) and abs(now.confidence - old.confidence) < 1e-9):
                print('综合数据库已改变')
                return True
        print('综合数据库未改变')
        return False
