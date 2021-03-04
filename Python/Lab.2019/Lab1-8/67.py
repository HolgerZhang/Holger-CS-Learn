"""
67.在程序中创建两个字典，找出并显示两个字典中具有相同值（要求数据类型也相同）的键
"""


def FindSameValue(dict1, dict2):
    SameValues = []
    for value in (v for v in dict1.values() if v in dict2.values()):
        if value not in SameValues:
            SameValues.append(value)
    SameValues = tuple(map(lambda x: (x, str(type(x))[7:-1]), SameValues))
    SameValuesKey1 = tuple([key for key in dict1.keys() if dict1[key] == item[0]]
                                                           for item in SameValues)
    SameValuesKey2 = tuple([key for key in dict2.keys() if dict2[key] == item[0]]
                                                           for item in SameValues)
    return tuple(zip(SameValues, SameValuesKey1, SameValuesKey2))


def Display(answer):
    if len(answer) == 0:
        print('两字典没有相同的值')
        return
    for item in range(len(answer)):
        print('两个字典都具有类型为{1}的值{0}'.format(*answer[item][0]))
        print('\t在字典1中的键为:', ' '.join(map(str, answer[item][1])))
        print('\t在字典2中的键为:', ' '.join(map(str, answer[item][2])))


if __name__ == "__main__":
    dict1 = {'q': [1], 's': '1', 'a': 3, 'c': 5, 'g': 5, 'w': 8, 'zz': 1}
    dict2 = {'a': '1', 'e': 1, 'q': 5, 'p': [1], 'wq': 1}
    Display(FindSameValue(dict1, dict2))
