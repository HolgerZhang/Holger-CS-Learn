# -*- coding: utf-8 -*-


def read_dict_file(dict_file_path: str, has_header=False):
    """
    读取词典
    :param has_header: 第一行是否有标识字数的
    :param dict_file_path: 字典路径
    :return: 字典（哈希表）, 词典中单个词语的最大长度
    """
    max_length = 0
    with open(dict_file_path, 'r', encoding='utf-8') as file:
        if has_header:
            _, max_length = map(int, file.readline().strip().split())
        try:
            words = []
            for item in map(lambda line: line.strip().split(), file.readlines()):
                words.extend(item)
        finally:
            file.close()
    if not has_header:
        max_length = max(map(lambda x: len(x), words))
    return set(words), max_length


def handle_corpus_file(corpus_file_path: str, output_file_path: str, handler=None, tee=False):
    """
    处理语料
    :param corpus_file_path: 语料文件路径
    :param output_file_path: 结构文件路径
    :param handler: 一个函数，接受语料中的一句话，将其分词，并返回拼接后的这句话
    :param tee: 三通，为 True 将处理前后的语句打印在屏幕上，否则不打印
    """
    if handler is None or not callable(handler):  # 防止 handler 不可调用而报错
        def handler(s):
            return s  # 默认什么都不做
    # 新建一个输出文件
    output_file = open(output_file_path, 'w', encoding='utf-8')
    output_file.close()
    with open(corpus_file_path, 'r', encoding='utf-8') as corpus_file:
        while True:  # 循环读取语料，每次一行
            line = corpus_file.readline()
            if not line:
                break
            sentence = line.strip()
            if tee:
                print("before: ", sentence)
            sentence = handler(sentence)
            if tee:
                print("after: ", sentence)
            # 向结果文件输出一行处理好的语料
            with open(output_file_path, 'a', encoding='utf-8') as output_file:
                output_file.write(sentence + '\n')


def segmentation_sentence(sentence: str, words: set, join_str=' ', max_length=10, only=None) -> str:
    """
    最大匹配算法 (双向最大匹配算法)
    :param sentence: 待分词句子
    :param words: 词典
    :param join_str: 拼接字符串
    :param max_length: 最大步长
    :param only: 仅使用某一算法进行分词，接受的参数为：'fmm'（前向最大匹配算法）, 'bmm'（逆向最大匹配算法）
    :return: 使用 join_str 拼接后的分词过的句子
    """

    def fmm(_sentence: str) -> list:
        """
        前向最大匹配算法
        :param _sentence: 待分词句子
        :return: 组成句子的词语
        """
        length = max_length
        seg = []
        while len(_sentence) > 0:
            word = _sentence[0:length]
            while word not in words:
                if len(word) <= 1:
                    break
                else:
                    length -= 1
                word = word[0:length]
            length = max_length
            seg.append(word)
            _sentence = _sentence[len(word):]
        return seg

    def bmm(_sentence: str) -> list:
        """
        逆向最大匹配算法
        :param _sentence: 待分词句子
        :return: 组成句子的词语
        """
        length = max_length
        seg = []
        while len(_sentence) > 0:
            word = _sentence[-length:]
            while word not in words:
                if len(word) <= 1:
                    break
                else:
                    length -= 1
                word = word[-length:]
            length = max_length
            seg.append(word)
            _sentence = _sentence[:-len(word)]
        seg.reverse()
        return seg

    # 用以支持使用单一的最大匹配算法来分词
    if only is not None:
        if only == 'fmm':
            return join_str.join(fmm(sentence))
        elif only == 'bmm':
            return join_str.join(bmm(sentence))
        else:
            raise ValueError('未知算法')

    # 分别应用前向最大匹配算法和逆向最大匹配算法对语句进行分词
    fmm_res = fmm(sentence)
    bmm_res = bmm(sentence)
    # 若前向和逆向分词结果词数不同，取分词数量较少的
    if len(fmm_res) < len(bmm_res):
        return join_str.join(fmm_res)
    elif len(fmm_res) > len(bmm_res):
        return join_str.join(bmm_res)
    else:
        fmm_single, bmm_single = 0, 0  # 前向和逆向分词结果中单字词语的数量
        same = True
        for x, y in zip(fmm_res, bmm_res):
            if x != y:
                same = False
            if len(x) == 1:
                fmm_single += 1
            if len(y) == 1:
                bmm_single += 1
        if same:
            # 分词结果相同，随便返回哪个都行
            return join_str.join(fmm_res)
        else:
            # 分词结果不同，返回单字词语的数量较少的
            if fmm_single <= bmm_single:
                return join_str.join(fmm_res)
            else:
                return join_str.join(bmm_res)


def evaluation(output_file_path: str, answer_file_path: str):
    """
    评价函数
    :param output_file_path: 结果文件
    :param answer_file_path: 答案文件
    :return: 真正例TP, 假正例FP, 假反例FN
    """

    def index_set(seg: list) -> set:
        """
        将词序列转换为词语在句子中的位置集合
        原因：直接将词转换为集合会失去位置信息，使用词语在句中的位置（起始位置和结束位置）来唯一地标识一个词
        :param seg: 词序列
        :return: 位置集合
        """
        seg_index_set = set()
        index = 0
        for word in seg:
            length = len(word)
            seg_index_set.add((index, index + length))
            index += length
        return seg_index_set

    def evaluation_sentence(output: list, answer: list):
        """
        评价一句话的分词结果
        :param output: 分词结果
        :param answer: 答案
        :return: 真正例TP, 假正例FP, 假反例FN
        """
        output_index_set = index_set(output)
        answer_index_set = index_set(answer)
        TP = len(output_index_set & answer_index_set)
        FP = len(output_index_set - answer_index_set)
        FN = len(answer_index_set - output_index_set)
        return TP, FP, FN

    TP_ALL, FP_ALL, FN_ALL = 0, 0, 0  # 全体的真正例TP, 假正例FP, 假反例FN
    with open(output_file_path, 'r', encoding='utf-8') as output_file, \
            open(answer_file_path, 'r', encoding='utf-8') as answer_file:
        while True:
            output_line = output_file.readline()
            answer_line = answer_file.readline()
            if not output_line and not answer_line:  # 已到达文件尾
                break
            if not output_line:  # 结果文件结束但答案文件未结束（有句子没输出）
                FN_ALL += len(answer_line.strip().split())  # 作为假反例
                continue
            elif not answer_line:  # 答案文件结束但结构文件未结束（多输出了其他的内容）
                FP_ALL += len(output_line.strip().split())  # 作为假正例
                continue
            evaluation_res = evaluation_sentence(output_line.strip().split(), answer_line.strip().split())
            TP_ALL += evaluation_res[0]
            FP_ALL += evaluation_res[1]
            FN_ALL += evaluation_res[2]
    return TP_ALL, FP_ALL, FN_ALL


def calculate_evaluation(TP, FP, FN):
    """
    计算查准率P、查全率R、F值
    :param TP: 真正例，这里是指识别出的个体总数
    :param FP: 假正例，这里是指结果中识别出来但不是真是的个体的数量
    :param FN: 假反例，这里是指测试集中存在但是没有识别出来的个体数量
    :return: 查准率P、查全率R、F值
    """
    P = TP / (TP + FP)  # TP + FP 为识别出的个体总数
    R = TP / (TP + FN)  # TP + FN 为测试集中存在的个体总数
    F = 2 * P * R / (P + R)
    return P, R, F
