#!/usr/bin/python3
# Project: Sort  File: generator.py
# Created by holger on 2020/12/14.
import os
import sys
import random

DATA_PATH = os.getcwd().replace('\\', '/') + '/data/'
DATA_NAME_FORMAT = 'data_{type}{size}.data'

# Make data folder
if os.path.isdir(DATA_PATH):
    pass
elif os.path.isfile(DATA_PATH):
    print('Failed to mkdir: file is already at', DATA_PATH)
    exit(1)
else:
    os.mkdir(DATA_PATH)


def file_name(kind: str, size: int) -> str:
    """
    Get file name of data file.
    :param kind: The Type of data file: random, positive or negative
    :param size: The size of sequence list.
    :return: File name of data file.
    """
    name = DATA_PATH + DATA_NAME_FORMAT.format(type=kind, size=size)
    question = '{} is already exist. Overwrite?[Y/n] '.format(name)
    # Force generation or not
    if os.path.isfile(name) and not sys.argv[-1].lstrip('-') == 'force':
        if input(question).strip().lower() != 'y':
            exit()
    return name


def creat_file(size: int):
    """
    Creat data file.
    :param size: The size of sequence list.
    :return: None
    """
    data_set = [random.randint(0, int(11 * size)) for _ in range(size)]
    with open(file_name('random', size), 'w', encoding='utf-8') as file:
        file.write(' '.join(map(str, data_set)))
    data_set.sort()
    with open(file_name('positive', size), 'w', encoding='utf-8') as file:
        file.write(' '.join(map(str, data_set)))
    data_set.reverse()
    with open(file_name('negative', size), 'w', encoding='utf-8') as file:
        file.write(' '.join(map(str, data_set)))


if __name__ == '__main__':
    for i in range(1, 5):
        creat_file(3 * 10 ** i)
    print('Data file created.')
