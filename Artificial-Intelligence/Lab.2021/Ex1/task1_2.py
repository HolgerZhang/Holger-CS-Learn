# -*- coding: utf-8 -*-

import word_seg

corpus_data = 'seg_data/corpus.sentence.txt'  # 语料
corpus_dict = 'seg_data/per.dict.txt'  # 字典
out_file = 'output/per.out.txt'  # 结果

if __name__ == '__main__':
    word_dict, max_len = word_seg.read_dict_file(corpus_dict, has_header=False)
    word_seg.handle_corpus_file(corpus_data, out_file,
                                handler=lambda s: word_seg.segmentation_sentence(s, word_dict, max_length=max_len))
