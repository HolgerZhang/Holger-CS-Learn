"""
66. 在程序中创建两个字典，找出并显示两个字典中相同的键。
"""


def FindSameKey(dict1, dict2):
    return list(set(dict1.keys()) & set(dict2.keys()))


if __name__ == "__main__":
    dict1 = {'q': 1, 's': 2, 'a': 3}
    dict2 = {'a': 2, 'e': 1, 'q': 5}
    print('The same key:', FindSameKey(dict1, dict2))
