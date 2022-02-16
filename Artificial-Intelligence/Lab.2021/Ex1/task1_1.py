# -*- coding: utf-8 -*-

import word_seg

corpus_data = 'seg_data/corpus.sentence.txt'  # 语料
corpus_dict = 'seg_data/corpus.dict.txt'  # 字典
ans_file = 'seg_data/corpus.answer.txt'  # 答案
out_file = 'output/corpus.out.txt'  # 结果

if __name__ == '__main__':
    word_dict, max_len = word_seg.read_dict_file(corpus_dict, has_header=True)
    word_seg.handle_corpus_file(corpus_data, out_file,
                                handler=lambda s: word_seg.segmentation_sentence(s, word_dict, max_length=max_len))
    tp, fp, fn = word_seg.evaluation(out_file, ans_file)
    p, r, f = word_seg.calculate_evaluation(tp, fp, fn)
    print('Precision = %d / %d = %.2f' % (tp, tp + fp, p * 100) + '%')
    print('Recall = %d / %d = %.2f' % (tp, tp + fn, r * 100) + '%')
    print('F = %.4f * %.4f * 2 / (%.4f + %.4f) = %.2f' % (p, r, p, r, f * 100) + '%')
