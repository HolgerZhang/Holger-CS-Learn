# -*- coding: utf-8 -*-

from relationship_extraction import Extractor

name_file = 'isA_AKO_shuffled_data/name_shuffled.txt'
tag_file = 'isA_AKO_shuffled_data/tag_shuffled.txt'
text_file = 'isA_AKO_shuffled_data/text.txt'
out_file = 'output/extract_result.txt'


def run(extractor: Extractor):
    Extractor.neatly_string(extractor.extract(), file=out_file)


def evaluate(extractor: Extractor):
    raw, res = extractor.eval()
    print('='*10, '测试用例', '='*10)
    print('\n'.join(raw))
    print('='*10, '运行结果', '='*10)
    print(Extractor.neatly_string(res))


if __name__ == '__main__':
    extractor = Extractor(name_file, tag_file, text_file)
    extractor.init()
    run(extractor)
    evaluate(extractor)
