# 找出所有最多带两位小数的整数
import re

pat1 = re.compile(r'-?\d+\.?\d*')
pat2 = re.compile(r'^-?\d+(\.\d{1,2})?$')
word = 'fgd hsjrg 12,4.ihfsnsfk23.45 fgklf12.4dfnl-23.45 fhgj-30.1ghllk-444.223'

index = 0
while True:
    res = pat1.search(word[index:])
    if not res:
        break
    index += res.end(0)
    find = res.group(0)
    ans = pat2.match(find)
    if ans:
        print(ans.group(0), end=' ')

# 结果： 12 23.45 12.4 -23.45 -30.1
