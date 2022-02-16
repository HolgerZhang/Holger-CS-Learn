from os import path

from control import Controller

folder = 'data'
rule_file = path.join(folder, 'rule-uncertain.txt')
basic_file = path.join(folder, 'knowledge-uncertain.txt')
aim_file = path.join(folder, 'aim-uncertain.txt')

Controller(rule_file=rule_file, basic_file=basic_file,
           aim_file=aim_file, file_generate_folder=folder).run()
