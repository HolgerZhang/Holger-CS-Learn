"""
62. 请利用正则表达式写一个 Python 程序以尝试解析 XML/HTML 标签。现有
    如下一段内容：
        <composer>Wolfgang Amadeus Mozart</composer>
        <author>Samuel Beckett</author>
        <city>London</city>
    希望自动格式化重写为：
        composer: Wolfgang Amadeus Mozart
        author: Samuel Beckett
        city: London
"""
import re


def analyzingHTML(s):
    pattern = re.compile(r"<(\w+)>(.+)</(\w+)>")
    result = []
    flag = 0
    while True:
        find = pattern.search(s[flag:])
        if not find:
            break
        result.append("".join((find.group(1), ": ", find.group(2))))
        flag += find.end(0)
    return '\n'.join(result)


if __name__ == "__main__":
    s = '''
            <composer>Wolfgang Amadeus Mozart</composer>
            <author>Samuel Beckett</author>
            <city>London</city>
        '''
    print(analyzingHTML(s))
