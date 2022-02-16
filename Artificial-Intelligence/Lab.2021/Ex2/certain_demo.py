from os import path

from control import Controller

folder = 'data'
rule_file = path.join(folder, 'rule-certain.txt')
basic_file = path.join(folder, 'knowledge-certain.txt')
aim_file = path.join(folder, 'aim-certain.txt')

Controller(rule_file=rule_file, basic_file=basic_file,
           aim_file=aim_file, file_generate_folder=folder).run()
