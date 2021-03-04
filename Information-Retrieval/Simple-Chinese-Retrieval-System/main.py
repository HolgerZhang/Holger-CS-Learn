# -*- coding: utf-8 -*-
# 作者：1927405160 张昊
# 主程序 ver 1.2，于2020-7-1 00:12:28停止修改（运行结果与第二次一致），预计得分+0.002?
import logging
from collections import Counter
from math import log10
from string import punctuation
from time import time

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(obj):
        return obj

# load settings data
from settings import *

# init global variable
corpus_data = []
corpus_number = 0
words_count = dict()
with open(STOP_WORDS_PATH, 'r', encoding=ENCODE) as stopFile:
    STOP_WORDS = eval(stopFile.read())
with open(OUTPUT_PATH, 'w', encoding=ENCODE):
    pass


# Decorator for logging
def info(arg):
    def set_log(func):
        def decorate():
            logging.basicConfig(level=logging.INFO, format='%(asctime)s [%(levelname)s] %(message)s')
            logger = logging.getLogger(PROJECT_NAME)
            logger.info(arg + '...')
            start = time()
            func()
            logger.info(arg + " done! Using %.5fs." % (time() - start))

        return decorate

    return set_log


# Calculation methods

def __analyze(sentence):
    return [s for s in sentence.strip().lower().split() if s not in punctuation and s not in STOP_WORDS]


def __max_tf_idf(word_list):
    words_bag = Counter(word_list)
    max_count = max(words_bag.items(), key=lambda item: item[1])[1]
    return {  # idf * modify_max_tf
        word: log10(corpus_number / words_count.get(word, 1e-6)) * (
                1 + words_bag.get(word, 1e-6) / (max_count ** KEY_PARAM)) for word in words_bag
    }


@info("Initializing")
def link_built_files():
    global corpus_data, corpus_number, words_count
    with open(CORPUS_DATA_PATH, 'r', encoding=ENCODE) as file:
        corpus_data = eval(file.read())
    corpus_number = len(corpus_data)
    with open(WORD_COUNTS_PATH, 'r', encoding=ENCODE) as file:
        words_count = eval(file.read())


@info("Building index")
def _build_index():
    global corpus_data, corpus_number
    corpus_data.clear()
    with open(RAW_CORPUS_PATH, encoding=ENCODE) as rawFile:
        lines = rawFile.readlines()
        corpus_number = len(lines)
        for line in lines:
            lst = line.strip().split('\t')
            corpus_data.append(dict(id=lst[0], document=lst[1].lower(), words=__analyze(lst[1]), tf_idf=dict()))


@info("Setting corpus")
def _get_tf_idf():
    global corpus_data, corpus_number, words_count
    words_count.clear()
    for i in range(corpus_number):
        for word in set(corpus_data[i]["words"]):
            words_count[word] = words_count.get(word, 0) + 1

    for i in range(corpus_number):
        corpus_data[i]["tf_idf"] = __max_tf_idf(corpus_data[i]["words"])

    with open(CORPUS_DATA_PATH, 'w', encoding=ENCODE) as file:
        file.write(str(corpus_data))
    with open(WORD_COUNTS_PATH, 'w', encoding=ENCODE) as file:
        file.write(str(words_count))


@info("Building")
def build():
    _build_index()
    _get_tf_idf()


def query(sentence: str, query_id: str):  # sorted by score * cosine
    global corpus_data, corpus_number, words_count
    sentenceList = __analyze(sentence)
    # score
    result = [[data_map["id"], sum((data_map["tf_idf"].get(word, 1e-6) for word in sentenceList))]
              for data_map in corpus_data]
    tf_idf_dict = __max_tf_idf(sentenceList)
    # cosine
    for x in range(corpus_number):
        dot_product, norm2_query, norm2_document = 1e-6, 1e-6, 1e-6
        for word in sentenceList:
            dot_product += tf_idf_dict[word] * corpus_data[x]["tf_idf"].get(word, 0)
            norm2_query += tf_idf_dict[word] ** 2
            norm2_document += corpus_data[x]["tf_idf"].get(word, 1e-6) ** 2
        result[x][1] *= dot_product / ((norm2_query * norm2_document) ** 0.5)
    # sort answers
    answer = [x[0] for x in sorted(result, key=lambda x: -x[1])[:10]]
    while len(answer) < 10:
        answer.append("D-1")
    with open(OUTPUT_PATH, 'a', encoding=ENCODE) as file:
        file.write(query_id + '\t' + ' '.join(answer) + '\n')


@info("Getting query answers")
def do_queries():
    with open(QUERY_PATH, 'r', encoding=ENCODE) as file:
        query_list = file.readlines()
    for i in tqdm(range(len(query_list))):
        this_query = query_list[i].strip().split("\t")
        query(this_query[1], this_query[0])


if __name__ == "__main__":
    build()
    # link_built_files()
    do_queries()
