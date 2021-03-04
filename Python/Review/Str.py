"""
    字符串与正则表达式有关固定解法
    index:
        ## 拼写检查程序: SpellCheck(s)
        ## 解析XML/HTML 标签: analyzingHTML(s)
        # # 姜老师的测试代码
"""
import re


def SpellCheck(s):
    """
    ## 拼写检查程序
    a) 两个或两个以上的空格出现时将其压缩为一个。
    b) 在标点符号后加上一个空格，如果这个标点符合之后还有字母。
    """
    return ' '.join(re.findall('\w+[,.!?:;]|\w+', s))


def analyzingHTML(s):
    """
    ## 解析XML/HTML 标签
    目标样式：标签名: 内容
    :param s:
    :return:
    """
    item = []
    for tag in re.findall('(?<=<)\w+', s):
        result = re.search('(?<=<' + tag + '>)[^<]+', s).group(0)
        item.append((tag, result))
    formatter = '{0[0]}: {0[1]}'.format
    return '\n'.join(map(formatter, item))


""" 姜老师的测试代码 """

# 1# RETest.py
# 以下是关于一些特殊正则表达式的验证，验证过程中采用了直接使用re模块的方法

# 或 '|' 元字符的两侧延伸特性
s = "pythop"
print(re.findall('python|p', s))  # 或 '|' 元字符在作用过程中总是尽可能地向两侧延伸
# ['p', 'p']
print()

# *和+的区别
s1 = "pythonn"
s2 = "pytho"
print(re.findall('python*', s1))  # ['pythonn']
print(re.findall('python+', s1))  # ['pythonn']
print(re.findall('python*', s2))  # ['pytho']
print(re.findall('python+', s2))  # []
print()

# 贪婪模式和非贪婪模式的效果对比
s = "pythonnnn"
print(re.findall('python*', s))  # 最后连续4个n将以0个或多个、且以贪婪模式全部视为匹配通过
# ['pythonnnn']
print(re.findall('python*?', s))  # 由于增加了？字符，将*原本的贪婪模式改为非贪婪模式，则最后连续的4个n将都不能出现在匹配结果中
# ['pytho']

# 因此，我们也许会认为*?的作用是肯定匹配0个目标字符，但这种理解绝对是错误的。
# 下面的例子中*和*？的结果是相同的。其是因为存在后面a字符的匹配要求，这将导致非贪婪模式会暂时失效。
# 也就是说，不管是贪婪模式还是非贪婪模式，都不是绝对的，需要看整个正则表达式整体的要求来做不同的处理
s = "pythonnnnabc"
print(re.findall('python*a', s))  # ['pythonnnna']
print(re.findall('python*?a', s))  # ['pythonnnna']
print()

# []的作用机制
# 在下面的例子中，如果将\d放在[]内部，由于\d本来就具有任选1个数字字符的作用，因此和[]的效果重叠了，也就是说有没有[]的效果是一样的
s = "abc123def 3456 pop"
print(re.findall('[\d]+', s))  # ['123', '3456']
print(re.findall('\d+', s))  # ['123', '3456']
print()

# 中括号中元字符的失效效应
'''
在中括号中，有一个特殊的规则：除\以外的元字符，其元字符的作用将会暂时屏蔽
第1个例子：在.和-前面各加了一个\，\.和\-都不能进行字符串转义，在正则转义时将确保.和-失去元字符作用，因此将.和-视为可选字符之一。
第2个例子：[]中出现了两段连续的4个\。以第1段\\\\为例，其字符串转义为\\，在正则转义阶段变为1个\，这将使\也会被视为可选字符之一。
            当然-前面的4个\也会进行相同的处理，也就是说这个例子的[]阶段中将有两个\视为可选字符，这并不会影响\的匹配。
            但事实上这个例子中的目标字符串中并没有\字符可供匹配。
第3个例子：经过字符串转义后，将变为第1个例子完全相同的情况了。
第4个例子：[]中的.和-将直接失去元字符的作用，因此将.和-视为可选字符之一。
因此这4个例子中的正则表达式对于当前的目标字符串的匹配和搜索结果完全是相同的。
'''
s = "ABCDEDFSDS.-"
print(re.findall('^[a-zA-Z]{1}[a-zA-Z0-9\.\-]{4,19}$', s))  # ['ABCDEDFSDS.-']
print(re.findall('^[a-zA-Z]{1}[a-zA-Z0-9\\\\.\\\\-]{4,19}$', s))  # ['ABCDEDFSDS.-']
print(re.findall('^[a-zA-Z]{1}[a-zA-Z0-9\\.\\-]{4,19}$', s))  # ['ABCDEDFSDS.-']
print(re.findall('^[a-zA-Z]{1}[a-zA-Z0-9.-]{4,19}$', s))  # ['ABCDEDFSDS.-']
print()
# 我们可以根据上面例子中的原理和规则自行分析下面两个例子的作用机制
s = "ABCDEDSDS\.-"
print(re.findall('^[a-zA-Z]{1}[a-zA-Z0-9\\.\-]{4,19}$', s))  # []
print(re.findall('^[a-zA-Z]{1}[a-zA-Z0-9\\\.\-]{4,19}$', s))  # ['ABCDEDSDS\\.-']
print()

# 字符串转义和正则转义的两个阶段
print(re.findall("\++", "a+b"))  # 无字符串转义，\+进行正则转义、匹配+字符，后面的+表示1个或多个
# ['+']
print(re.findall("\++", "a++b"))  # 同上
# ['++']
print(re.findall("\\++", "a++b"))  # \\进行字符串转义、得到\++，然后同上
# ['++']
print(re.findall(r"\++", "a++b"))  # 原生字符串，不进行字符串转义，结果同上
# ['++']
print(re.findall(r"\\+", "a++b"))  # 原生字符串，不进行字符串转义，\\通过正则转义后理解为匹配1个或多个\字符，因此本例无匹配结果
# []

# escape函数的作用机制。自行根据每个例子的结果理解escape函数的作用机制
print(re.escape("+"))  # \+
print(re.escape("abc"))  # abc
print(re.escape("."))  # \.
res = re.escape("\\")
print(re.escape("\\"))  # \\


# 2# match_object.py
'''
下面基于一个无子模式（成组）的正则表达式，说明正则表达式对象的search方法和findall方法的具体使用方法
在不存在子模式的条件下，match对象的group函数在使用时不需要提供实参，其使用默认值0。
group（0）表示取得正则表达式整体所匹配的结果字符串。同样的，start、end和span函数也有默认值0
'''
telNumber = "Suppose my Phone No. is 0535-1234567, yours is 010-12345678, his is 025-87654321."
pat = re.compile(r"\d+-\d+")  # 该正则表达式中的-不是表示范围的元字符，因为其只能在[]中表示范围的元字符
index = 0
while True:
    m = pat.search(telNumber, index)
    # 但不能在re模块的search函数中指定搜索区间的开始和结束位置。以下search函数的调用存在语法错误
    #    m = re.search(r"\d+-\d+", telNumber, index)
    if not m:
        break
    print(m.group(), m.start(), m.end(), m.span())
    index = m.end()

print(pat.findall(telNumber))

# 0535-1234567 24 36 (24, 36)
# 010-12345678 47 59 (47, 59)
# 025-87654321 68 80 (68, 80)
# ['0535-1234567', '010-12345678', '025-87654321']


# 3# match_search_findall.py
'''
findall能在目标字符串中搜索到所有的结果子串，并直接以字符串的列表的形式来返回结果
match和search仅能搜索一次，match从指定的位置开始搜索，search能在整个字符串范围内搜索。
match和search返回的数据是match对象，使用稍麻烦一些，但却能获得比findall结果更多的信息，如开始和结束的位置
'''
s = "www.baidu.com www.baidu.edu.cn"

pat = r"baidu\."
print(re.findall(pat, s))  # ['baidu.', 'baidu.']
print(re.match(pat, s))  # None
print(re.search(pat, s))  # <re.Match object; span=(4, 10), match='baidu.'>


# 4# group_re.py
# 子模式例1
'''
下面的正则表达式中有两个子模式。
有子模式的正则表达式的作用机制是首先按照整个正则表达式进行匹配，然后在结果中突出子模式所匹配通过的字符串部分。
对下例，整个正则表达式匹配整个目标字符串一次，www.匹配了www\.部分，基于贪婪的原则(.*)部分总是尽可能多的匹配更多的满足条件的字符串，直至
遇到了最后的(\..{3})匹配了最后的.org部分。
在最终的结果中，仅给出了两个子模式所对应的匹配结果，以列表的形式出现。由于正则表达式在对目标字符串进行匹配时仅匹配成功1轮，因此这个列表
中只有1个元素；这个元素中的数据需要对应2个子模式的结果，这两个子模式匹配成功的子串将以元组的形式来进行封装。
'''
m = re.findall(r'www\.(.*)(\..{3})', 'www.python.org  www.python11111.org')
print(m)  # [('python.org  www.python11111', '.org')]
print()

# 子模式例2
'''
下面的正则表达式中子模式（组）包括了中括号所标记的可选字符部分以及相应的数量修饰符，
在结果中出现的是匹配通过字符串中除掉首字母部分的字符串，也就是'BCDEDFSDS.-'
'''
pat = re.compile('^[a-zA-Z]{1}([a-zA-Z0-9.-]{4,19})$')
print(pat.findall("ABCDEDFSDS.-"))  # ['BCDEDFSDS.-']

'''
下面的正则表达式中子模式（组）仅包括了中括号所标记的可选字符部分，
配合后面的数量修饰符一起作用的过程中，在结果中出现的是最后一次匹配成功的字符串，也就是"-"
'''
pat = re.compile('^[a-zA-Z]{1}([a-zA-Z0-9.-]){4,19}$')
print(pat.findall("ABCDEDFSDS.-"))  # ['-']
print()

# 子模式例3
'''
正则表达式中存在子模式时，在匹配过程中，首先将整个表达式整体去匹配目标字符串，我们将可能得到的匹配结果字符串称为0号结果字符串。
然后按照子模式关系再得到各子模式在0号结果字符串中分别得到各子模式所对应的1号、2号结果字符串。这就是分组和子模式所带来的功能和影响。
在此条件下，如果我们使用search和match方法，将可以通过match对象丰富的方法来得到例如结果字符串的起始位置等更加详细的信息。
另外一个方面，findall方法仅能返回各子模式所对应的结果字符串所构成的列表。

match对象的主要成员：
lastindex：表示子模式的最大编号，从1开始计数，如无子模式等于None
groups（）：将每个子模式的匹配结果字符串作为元素构成的元组，如无子模式则返回空元组
group（index=0）：返回各子模式对应的匹配结果字符串。参数从1开始计数表示对应哪个子模式，最大值取决于子模式数量。默认值为0表示整个正则表达式对应的匹配结果字符串
start（index=0）：返回各子模式对应匹配结果的开始下标。参数含义同group函数
end（index=0）：返回各子模式对应匹配结果的实际结束位置下一个字符的下标。参数含义同group函数
span(index=0):返回各子模式对应匹配结果的开始位置和结束位置，以元组的形式来提供
'''
telNumber = "Suppose my Phone No. is 0535-1234567, yours is 010-12345678, his is 025-87654321."
pat = re.compile(r"(\d+)-(\d+)")  # 请思考：如果我们将其中的+移到小括号外面来，将获得什么匹配结果？
index = 0
while True:
    m = pat.search(telNumber, index)
    if not m:
        break
    print(m.lastindex, m.groups(),
          m.group(0), m.start(0), m.end(0), m.span(0),
          '\t', m.group(1), m.start(1), m.end(1), m.span(1),
          '\t', m.group(2), m.start(2), m.end(2), m.span(2))
    index = m.end(0)  # 写为end(2)也有相同结果

print(pat.findall(telNumber))  # 和match和search相比，有子模式存在的情况下，findall仅返回子模式所对应的匹配结果

# 2 ('0535', '1234567') 0535-1234567 24 36 (24, 36) 	 0535 24 28 (24, 28) 	 1234567 29 36 (29, 36)
# 2 ('010', '12345678') 010-12345678 47 59 (47, 59) 	 010 47 50 (47, 50) 	 12345678 51 59 (51, 59)
# 2 ('025', '87654321') 025-87654321 68 80 (68, 80) 	 025 68 71 (68, 71) 	 87654321 72 80 (72, 80)
# [('0535', '1234567'), ('010', '12345678'), ('025', '87654321')]
