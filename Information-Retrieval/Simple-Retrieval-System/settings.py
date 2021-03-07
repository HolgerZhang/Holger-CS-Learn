# -*- coding: utf-8 -*-
# 作者：1927405160 张昊
# settings v1.2

# Basic settings
ENCODE = "utf-8"  # 编码方式, DO NOT change
KEY_PARAM = 0.82  # 魔改后tf-idf计算公式中的一个关键参数, DO NOT change
PROJECT_NAME = 'Searching System 2'  # 项目名称

# Runtime Setting
# 1. Raw Data source, DO NOT change
RAW_CORPUS_PATH = "data\\documents.txt"  # document path, MUST exists, DO NOT change
STOP_WORDS_PATH = "data\\STOPWORDS"  # stop words path, MUST exists, DO NOT change
# 2. Index Data source, DO NOT change
CORPUS_DATA_PATH = "index_files\\CORPUS_DATA"  # store index data struct, DO NOT change
WORD_COUNTS_PATH = "index_files\\WORD_COUNTS"  # store words counter data, DO NOT change

# Query settings for 1000 questions
QUERY_PATH = "data\\quesions.txt"  # query data file, MUST exists
OUTPUT_PATH = "out\\result.txt"  # result file path & name
