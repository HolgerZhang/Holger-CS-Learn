"""
52. 给定如下一段英文
        A major drawback of cross-network recommender solutions is that they can only
        be applied to users that are overlapped across networks. Thus, the non-overlapped
        users, which form the majority of users are ignored. As a solution, we propose
        CnGAN, a novel multi-task learning based recommend architecture。
    编写一个函数，要求实现以下功能：1）统计有多少个不同的单词；2）根据
    每个单词 ASCII 码值的和对单词进行从小到大的排序，重复出现的单词只算一
    次的和，按行输出单词及对应的和。
"""
import re


def FindWords(s):
    pattern = re.compile("[A-Za-z-]+")
    words = sorted(map(lambda w: (w, sum(map(ord, re.findall("[A-Za-z]", w)))),
                       list(set(pattern.findall(s)))),
                   key=lambda x: x[1])
    return len(words), words


if __name__ == "__main__":
    st = 'A major drawback of cross-network recommender solutions is that they can only be applied to users that are ' \
         'overlapped across networks. Thus, the non-overlapped users, which form the majority of users are ignored. ' \
         'As a solution, we propose CnGAN, a novel multi-task learning based recommend architecture. '
    s, lst = FindWords(st)
    print('There are %d words in the paragraph.' % s)
    for i in range(s):
        print(*lst[i])
