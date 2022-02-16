# 实验二：产生式系统

1927405160 张昊

## 实验环境

Python 3.9

依赖包：

- easydict
- fuzzywuzzy
- python-Levenshtein（可选）

## 项目结构

```
certain_demo.py  确定性推理样例程序
control.py  控制系统
data/  运行数据目录
integrated_database.py  综合数据库
output/  运行结果转储目录
readme.md  说明文档
reasoner.py  推理机
requirements.txt  依赖项
rule_base.py  知识库（规则库）
uncertain_demo.py  不确定性推理样例程序
```

## 运行方法

必要的输入文件位于 data 目录下，有三个:

-  *rule.txt*:规则库文件，格式为(每条规则一行，不区分关键字 if then 的大小写): `IF E1 AND E2 AND E3 THEN D [置信度]`
  其中 [置信度] 可以省略，默认为 1.0 
- *knowledge.txt*:综合数据库文件，格式为(每条事实一行，于置信度用空格隔开): `事实 置信度`
- *aim.txt*:目标结论集合，每条可能的目标结论一行。 根据输入规则和事实的不同，程序会自动识别并提供确定性和非确定性的推理。

 产生式系统使用菜单驱动，有如下功能:
 [0] 开始运行(进行推理，会输出运行过程)
 [1] 添加规则
 [2] 删除规则
 [3] 添加事实
 [4] 删除事实
 [5] 打印规则库
 [6] 打印综合数据库
 [7] 保存规则库(到文件)
 [8] 保存综合数据库(到文件)

给出了两个例子，输入数据存放在 data 文件夹，运行过程存放在 output 文件夹下。 

1. 确定性推理 certain_demo.py:

   使用如下的规则库 rule-certain.txt 综合数据库 knowledge-certain.txt

   运行：

   ```bash
   $ python3 certain_demo.py
   ```

   根据菜单提示运行即可。

2. 不确定性推理 uncertain_demo.py:

   使用如下的规则库 rule-uncertain.txt 综合数据库 knowledge-uncertain.txt

   运行：

   ```bash
   $ python3 uncertain_demo.py
   ```

   根据菜单提示运行即可。

   