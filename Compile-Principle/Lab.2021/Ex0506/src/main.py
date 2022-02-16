import sys

from parser import Grammar, SLR


def read_file(file_name: str):
    with open(file_name, 'r', encoding='utf-8') as file:
        text = file.read().strip()
    return text


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print('Invalid arguments!', file=sys.stderr)
        exit(1)
    grammar = Grammar(read_file(sys.argv[1]))
    print(SLR(grammar).parser(read_file(sys.argv[2])))
