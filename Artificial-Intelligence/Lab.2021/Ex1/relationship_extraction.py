# -*- coding: utf-8 -*-
import math
import re
import sys
from random import choice

import jieba
from easydict import EasyDict as EDict
from tqdm import tqdm

from word_seg import segmentation_sentence

CONFIG = EDict({
    'encoding': 'utf-8',
    'sentence_max_count': 1,
    'stop_words': {'。', '？', '！', ':', ';', '；', '：', '《', '》', '、', ' '},
    'relation_start_words': {'简介', '介绍', '类型', '说明', '类型'},
    'isa_words': {'是', '从属', '附属', '归属', '包括', '包含', '蕴含', '囊括'},
    'accelerated_words': {'小说', '电影', '游戏', '公司', '企业', '学院'},
    'eval_number': 10,
    'relation_number_limit': 3,
})


class Extractor:
    def __init__(self, name_file, tag_file, text_file):
        self._name_file = name_file
        self._tag_file = tag_file
        self._text_file = text_file
        self.names = set()
        self.tags = set()
        self.text_data = []

    def init(self):
        self.names = self.read_dict(self._name_file)
        print(f'读取实体 {len(self.names)} 个', file=sys.stderr)
        self.tags = self.read_dict(self._tag_file)
        print(f'读取标签 {len(self.tags)} 个', file=sys.stderr)
        self.text_data = self.read_text(self._text_file)
        print(f'{len(self.text_data)} 行文本加载完成', file=sys.stderr)
        pass

    @staticmethod
    def read_dict(file_name: str) -> set:
        result = set()
        with open(file_name, 'r', encoding=CONFIG.encoding) as file:
            for line in file.readlines():
                line = line.strip()
                if len(line) != 0:
                    result.add(line)
                    result.add(re.sub('|'.join(CONFIG.stop_words), '', line))
        temp_file = file_name + '.tmp'
        with open(temp_file, 'w', encoding=CONFIG.encoding) as file:
            file.write('\n'.join(result))
        jieba.load_userdict(temp_file)
        return result

    @staticmethod
    def read_text(file_name: str) -> list:
        with open(file_name, 'r', encoding=CONFIG.encoding) as file:
            result = [line.strip() for line in file.readlines() if len(line.strip()) != 0]
        return result

    @staticmethod
    def __handle_sentence(sentence: str) -> list:
        # 分句，并将句子转换为词列表，只考虑前 $(CONFIG.sentence_max_count) 个句子，并去除停用词以及大部分标点符号
        sentence = re.sub('。?(%+)', '，', sentence)
        sentence = re.sub('#+|-{3,}', '', sentence)
        words = []
        _cnt = 0
        for sentence in filter(lambda x: len(x.strip()) != 0 and x.find('。') == -1,
                               re.split(r'(\s*。\s*)', sentence)):
            _words = jieba.lcut(sentence)
            words.append(EDict({
                'sentence': ''.join(_words),
                'words': [word for word in _words if word not in CONFIG.stop_words],
            }))
            _cnt += 1
            if _cnt >= CONFIG.sentence_max_count:
                break
        return words

    @staticmethod
    def __find_name_in_sentence(sentence: list, names: set):
        # 查找句子中首次出现在实体集中的实体，未找到返回None
        for word in sentence:
            if word in names:
                return word
        return None

    @staticmethod
    def __find_tags_in_sentence(sentence_words: list, first_name: str, tags: set) -> list:
        # 查找标签
        max_length = max(map(len, tags))

        def find_value(string_list: list, value: str) -> int:
            for index, string in enumerate(string_list):
                if string == value or string.find(value) != -1:
                    return index
            return -1

        def _find_tag(string_list: list, reverse=False):
            if reverse:
                for word in reversed(string_list):
                    if word in tags:
                        return word
                for word in reversed(
                        segmentation_sentence(''.join(string_list), tags, max_length=max_length).split()):
                    if len(word) > 1 and word in tags:
                        return word
            else:
                for word in string_list:
                    if word in tags:
                        return word
                for word in segmentation_sentence(''.join(string_list), tags, max_length=max_length).split():
                    if len(word) > 1 and word in tags:
                        return word
            return None

        result = []
        _result_set = set()
        need_next = True
        for key in CONFIG.relation_start_words:
            need_next = True
            index = find_value(sentence_words, key)
            if index != -1:
                found1 = _find_tag(sentence_words[:index], reverse=True)
                if found1 is not None and found1 not in _result_set:
                    _result_set.add(found1)
                    result.append(found1)
                    # need_next = False
                found2 = _find_tag(sentence_words[:index])
                if found2 is not None and found2 not in _result_set:
                    _result_set.add(found2)
                    result.append(found2)
                    # need_next = False
                if found1 is None and found1 is None:
                    found = _find_tag(sentence_words[index + 1:])
                    if found is not None and found not in _result_set:
                        _result_set.add(found)
                        result.append(found)
                    found = _find_tag(sentence_words[index + 1:], reverse=True)
                    if found is not None and found not in _result_set:
                        _result_set.add(found)
                        result.append(found)
        if need_next:
            for key in CONFIG.isa_words:
                index = find_value(sentence_words, key)
                if index != -1:
                    for acc_word in CONFIG.accelerated_words:
                        acc_found = find_value(segmentation_sentence(first_name, tags, max_length=max_length).split(),
                                               acc_word)
                        if acc_found != -1 and acc_word not in _result_set:
                            _result_set.add(acc_word)
                            result.append(acc_word)
                    else:
                        for last in ('，', ','):
                            last_index = find_value(sentence_words, last)
                            if last_index != -1:
                                found = _find_tag(sentence_words[index + 1:last_index], reverse=True)
                                if found is not None and found not in _result_set:
                                    _result_set.add(found)
                                    result.append(found)
                        found = _find_tag(sentence_words[index + 1:], reverse=True)
                        if found is not None and found not in _result_set:
                            _result_set.add(found)
                            result.append(found)
                        found = _find_tag(sentence_words[index + 1:])
                        if found is not None and found not in _result_set:
                            _result_set.add(found)
                            result.append(found)
        return result  # 越靠前的标签认为是最符合的标签

    def __extract(self, texts: list) -> list:
        result = []
        for text in tqdm(texts):
            for sentence in self.__handle_sentence(text):  # 分句，并将句子处理成为词列表
                first_name = self.__find_name_in_sentence(sentence.words, self.names)  # 首次出现在实体集中的实体
                if first_name is not None:
                    all_tags = self.__find_tags_in_sentence(sentence.words, first_name, self.tags)  # 找到所有标签
                    if len(all_tags) != 0:
                        result.append(EDict({
                            'name': first_name,
                            'tags': all_tags,
                            'sentence': sentence.sentence,
                        }))
        return result

    def extract(self) -> list:
        return self.__extract(self.text_data)

    def eval(self):
        data = set()
        while len(data) < CONFIG.eval_number:
            data.add(choice(self.text_data))
        data = list(data)
        return data, self.__extract(data)

    @staticmethod
    def neatly_string(result, file=None):
        output = ''
        for item in tqdm(result):
            cnt = 0
            for tag in item.tags:
                if tag.isdigit():
                    continue
                output += f'[{item.name}, isA, {tag}]  {item.sentence}\n'
                cnt += 1
                if cnt >= math.floor(len(item.tags) / CONFIG.relation_number_limit):  # 缩减冗余的标签，提高accuracy
                    break
        if file:
            with open(file, 'w', encoding=CONFIG.encoding) as f:
                f.write(output)
        return output
