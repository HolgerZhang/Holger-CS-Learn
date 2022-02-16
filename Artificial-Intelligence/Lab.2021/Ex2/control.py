import time

from easydict import EasyDict

from integrated_database import Database, Fact
from reasoner import Reasoner
from rule_base import RuleBase


class Controller:
    CHOICE = EasyDict({
        'exec': 0,
        'add_rule': 1,
        'delete_rule': 2,
        'add_fact': 3,
        'delete_fact': 4,
        'show_rules': 5,
        'show_db': 6,
        'save_rules': 7,
        'save_db': 8,
        'quit': 9,
    })
    MENU = f"请选择下一步动作：\n" \
           f"[{CHOICE.exec}] 开始运行\n" \
           f"[{CHOICE.add_rule}] 添加规则\n" \
           f"[{CHOICE.delete_rule}] 删除规则\n" \
           f"[{CHOICE.add_fact}] 添加事实\n" \
           f"[{CHOICE.delete_fact}] 删除事实\n" \
           f"[{CHOICE.show_rules}] 打印规则库\n" \
           f"[{CHOICE.show_db}] 打印综合数据库\n" \
           f"[{CHOICE.save_rules}] 保存规则库\n" \
           f"[{CHOICE.save_db}] 保存综合数据库\n" \
           f"[{CHOICE.quit}] 退出程序"

    def __init__(self, rule_file: str, basic_file: str, aim_file: str, file_generate_folder: str):
        self.rule_base: RuleBase = RuleBase()
        self.rule_base.read(rule_file, aim_file)
        self.database: Database = Database()
        self.database.read(basic_file)
        self.reasoner: Reasoner = Reasoner(self.rule_base, self.database)
        self.finished: bool = False
        self.result = None
        self.file_generate_folder: str = file_generate_folder

    def run(self):
        while True:
            print(Controller.MENU)
            choice = input('>>> ')
            try:
                choice = int(choice)
            except Exception:
                print('未知的选项，请输入整数！')
                continue
            if choice == Controller.CHOICE.exec:
                if self.finished:
                    print('已经成功运行，详情请查看历史记录')
                    if self.result is None:
                        print('未能匹配到结论')
                    else:
                        print('结论为', self.result)
                    continue
                st_time = time.time()
                self.__exec()
                print(f'运行结束，耗时：{time.time() - st_time}秒')
                self.finished = True
            elif choice == Controller.CHOICE.add_rule:
                self.__add_rule()
            elif choice == Controller.CHOICE.delete_rule:
                self.__delete_rule()
            elif choice == Controller.CHOICE.add_fact:
                self.__add_fact()
            elif choice == Controller.CHOICE.delete_fact:
                self.__delete_fact()
            elif choice == Controller.CHOICE.show_rules or choice == Controller.CHOICE.show_db:
                self.__show(choice)
            elif choice == Controller.CHOICE.save_rules or choice == Controller.CHOICE.save_db:
                self.__save(choice)
            elif choice == Controller.CHOICE.quit:
                print('Bye~')
                break
            else:
                print('未知的选项！')

    def __exec(self):
        self.result = self.reasoner.reasoning()
        if self.result is None:
            print('未能匹配到结论')
        else:
            print('结论为', self.result)

    def __add_rule(self):
        raw_rule = input('请输入要新增的规则：')
        try:
            if self.rule_base.add(raw_rule):
                print('规则新增成功')
            else:
                print('规则不合法')
        except Exception as e:
            print('规则新增失败:', *e.args)

    def __delete_rule(self):
        print(self.rule_base.list())
        try:
            index = int(input('请选择要删除的规则: '))
            self.rule_base.delete(index)
            print('规则删除成功')
        except Exception as e:
            print('输入不合法:', *e.args)

    def __add_fact(self):
        try:
            raw_rule = input('请输入要新增的事实：')
            p = float(input('请输入新增事实的置信度：'))
            self.database.add(Fact(raw_rule, p))
            print('事实新增成功')
        except Exception as e:
            print('事实新增失败:', *e.args)

    def __delete_fact(self):
        for i, x in enumerate(self.database.data):
            print(f'[{i}] {x}')
        try:
            index = int(input('请选择要删除的事实: '))
            self.database.delete(index)
            print('事实删除成功')
        except Exception as e:
            print('输入不合法:', *e.args)

    def __show(self, option: int):
        if option == Controller.CHOICE.show_rules:
            print(self.rule_base.list())
        elif option == Controller.CHOICE.show_db:
            for i, x in enumerate(self.database.data):
                print(f'[{i}] {x}')

    def __save(self, option: int):
        timestamp = time.strftime("%Y%m%d%H%M%S", time.localtime())
        if option == Controller.CHOICE.save_rules:
            save_path = f'{self.file_generate_folder}/rule-{timestamp}.txt'
            self.rule_base.write(save_path)
            print(f'文件 {save_path} 写入成功')
        elif option == Controller.CHOICE.save_db:
            save_path = f'{self.file_generate_folder}/knowledge-{timestamp}.txt'
            self.database.write(save_path)
            print(f'文件 {save_path} 写入成功')
