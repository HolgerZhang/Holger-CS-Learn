## 个人的银行账户管理程序    BankAccount

*2020/02/04*  By Holger.

主要来自于《Ｃ＋＋语言程序设计（第四版）》（郑莉  清华大学出版社）中的综合实例部分。



### 使用说明

1. 本程序可以保存运行状态到文本文件（通过保存修改状态的用户输入的命令实现），有关如何打开保存了运行状态存档的文件。

2. 运行程序

   (1) 程序直接执行

   *例如*　在Windows下可以在命令提示符（cmd）中定位到文件所在文件夹后输入```BankAccount.exe```直接打开；在Linux下可以在终端中定位到文件所在文件夹后输入```./BankAccount```直接打开。

   其输入数据默认保存为当前运行文件夹下的文本文件类型```"command_this_runtime.account"```中，且下次打开时继续上一次的运行状态。

   (2) 打开某时运行状态存档

   *例如*　在Windows下可以在命令提示符（cmd）中定位到文件所在文件夹后输入```BankAccount.exe　文件名```直接打开；在Linux下可以在终端中定位到文件所在文件夹后输入```./BankAccount　文件名```直接打开。

   *其中文件名可以是全路径文件名，也可以是当前运行目录下的文件名*

   这个文件以文本的形式储存了某一时刻的记录，而且本次正确运行的命令会保存到这个文件。

3. 程序使用

   程序使用命令语句来实现各种功能，一条语句占一行。

   具体语法可以参考程序运行时的提示信息或以下说明：

   - 输入命令位置：在　```日期	Total: ＊＊＊＊	>>>　```　后输入

     *其中Total后面为账户总金额*

   - 添加账户：
   
      储蓄账户：```a s 账户id 年利率```

      储蓄账户：```a c 账户id 信用额度 年利率 年费```

   - 存款：```d 账户序号 金额 说明信息```

   - 取款：```w 账户序号 金额 说明信息```

   - 显示账户信息：```s```

   - 改变日期中的日：```c day```

   - 下一个月：```n```

   - 查询账户明细：```q 开始日期 结束日期```　日期严格按照格式```yyyy-mm-dd```

   - 退出系统：```e```



### 文件结构

- 源码部分    /
  - account.h
    - AccountRecord类声明：用于记录账目数据，便于历史记录的查询
    - AccountException类声明与实现：派生自runtime_error，用于处理与账户有关的错误信息
    - 基类 Account类声明
    - 派生类 SavingsAccount类声明：储蓄账户
    - 派生类 CreditAccount类声明：信用卡账户
  - date.h  Date类声明：用于日期的记录
  - accumulator.h  Accumulator类声明与实现：用于获取到某个日期的金额按日累加和
  - controller.h  Controller类声明：用于运行控制
  - account.cpp
    - AccountRecord类实现
    - 基类 Account类实现
    - 派生类 SavingsAccount类实现
    - 派生类 CreditAccount类实现
  - date.cpp  Date类实现
  - controller.cpp  Controller类实现
  - main.cpp  主程序以及错误捕获处理程序
  - README.md  说明文档
- 编译文件与示例    /Build
  - Windows 系统    /Build/Windows
    - BankAccount.exe  可执行文件
    - example.account  运行示例数据文件
  - Linux 系统    /Build/Linux
    - BankAccount  可执行文件
    - example.account  运行示例数据文件



### 示例

#### Windows系统下的示例:

**第一次运行（cmd.exe）**

```
E:\Files\Document>BankAccount.exe example.account
Default date: 2019-11-01.

Welcome! Enter the command after ">>>".
  =======================COMMAND=======================
        Add account(a type id [credit] rate [fee])
          TYPE:[s]SavingsAccount -> id rate
               [c]CreditAccount  -> id credit rate fee
        Deposit    (d account amount desc)
        Withdraw   (w account amount desc)
        Show       (s)
        Change Day (c day)
        Next Month (n)
        Query      (q yyyy-mm-dd yyyy-mm-dd)
        Exit       (e)
  =====================================================

Commands:
2019-11-1       Total: 0        >>> a s S4030050 0.018
2019-11-1       #S4030050 is created.
2019-11-1       Total: 0        >>> a s 01927405 0.018
2019-11-1       #01927405 is created.
2019-11-1       Total: 0        >>> c 5
2019-11-5       Total: 0        >>> a c C0628001 30000 0.0005 30
2019-11-5       #C0628001 is created.
2019-11-5       Total: 0        >>> c 8
2019-11-8       Total: 0        >>> d 0 8200 salary
2019-11-8       #S4030050       8200    8200     salary
2019-11-8       Total: 8200     >>> c 11
2019-11-11      Total: 8200     >>> w 2 6000 buy a iPhone
2019-11-11      #C0628001       -6000   -6000    buy a iPhone
2019-11-11      Total: 2200     >>> c 26
2019-11-26      Total: 2200     >>> d 1 10000 sell stock 1000
2019-11-26      #01927405       10000   10000    sell stock 1000
2019-11-26      Total: 12200    >>> n
2019-12-1       #C0628001       -60     -6060   Interest
2019-12-1       Total: 12140    >>> d 2 6060 repay the credit
2019-12-1       #C0628001       6060    0        repay the credit
2019-12-1       Total: 18200    >>> c 8
2019-12-8       Total: 18200    >>> d 0 8300 salary
2019-12-8       #S4030050       8300    16500    salary
2019-12-8       Total: 26500    >>> c 12
2019-12-12      Total: 26500    >>> w 2 2000 buy a television
2019-12-12      #C0628001       -2000   -2000    buy a television
2019-12-12      Total: 24500    >>> n
2020-1-1        #S4030050       31.66   16531.7 Interest
2020-1-1        #01927405       17.75   10017.8 Interest
2020-1-1        #C0628001       -20     -2020   Interest
2020-1-1        #C0628001       -30     -2050   Annual fee
2020-1-1        Total: 24499.4  >>> s
[0] S4030050    Balance: 16531.7
[1] 01927405    Balance: 10017.8
[2] C0628001    Balance: -2050  Available credit: 27950
2020-1-1        Total: 24499.4  >>> d 2 2050 repay the credit
2020-1-1        #C0628001       2050    0        repay the credit
2020-1-1        Total: 26549.4  >>> q 2019-11-01 2019-11-30
2019-11-1       #S4030050       0       0       Creation
2019-11-1       #01927405       0       0       Creation
2019-11-5       #C0628001       0       0       Creation
2019-11-8       #S4030050       8200    8200     salary
2019-11-11      #C0628001       -6000   -6000    buy a iPhone
2019-11-26      #01927405       10000   10000    sell stock 1000
2020-1-1        Total: 26549.4  >>> q 2019~12~01 2019~12~31
Bad line in <stdin> q 2019~12~01 2019~12~31
Error: Invalid date
2020-1-1        Total: 26549.4  >>> e
Program finished.
```

**第一次运行后`example.acconut`文件内容**

```
# Runtime Example for Windows
# encoding: utf-8
a s S4030050 0.018
a s 01927405 0.018
c 5
a c C0628001 30000 0.0005 30
c 8
d 0 8200 salary
c 11
w 2 6000 buy a iPhone
c 26
d 1 10000 sell stock 1000
n
d 2 6060 repay the credit
c 8
d 0 8300 salary
c 12
w 2 2000 buy a television
n
d 2 2050 repay the credit
```

**第二次运行（cmd.exe）**

```
E:\Files\Document>BankAccount.exe example.account
Default date: 2019-11-01.
History:
2019-11-1       #S4030050 is created.
2019-11-1       #01927405 is created.
2019-11-5       #C0628001 is created.
2019-11-8       #S4030050       8200    8200     salary
2019-11-11      #C0628001       -6000   -6000    buy a iPhone
2019-11-26      #01927405       10000   10000    sell stock 1000
2019-12-1       #C0628001       -60     -6060   Interest
2019-12-1       #C0628001       6060    0        repay the credit
2019-12-8       #S4030050       8300    16500    salary
2019-12-12      #C0628001       -2000   -2000    buy a television
2020-1-1        #S4030050       31.66   16531.7 Interest
2020-1-1        #01927405       17.75   10017.8 Interest
2020-1-1        #C0628001       -20     -2020   Interest
2020-1-1        #C0628001       -30     -2050   Annual fee
2020-1-1        #C0628001       2050    0        repay the credit

Welcome! Enter the command after ">>>".
  =======================COMMAND=======================
        Add account(a type id [credit] rate [fee])
          TYPE:[s]SavingsAccount -> id rate
               [c]CreditAccount  -> id credit rate fee
        Deposit    (d account amount desc)
        Withdraw   (w account amount desc)
        Show       (s)
        Change Day (c day)
        Next Month (n)
        Query      (q yyyy-mm-dd yyyy-mm-dd)
        Exit       (e)
  =====================================================

Commands:
2020-1-1        Total: 26549.4  >>> c 8
2020-1-8        Total: 26549.4  >>> d 0 9000 salary
2020-1-8        #S4030050       9000    25531.7  salary
2020-1-8        Total: 35549.4  >>> w 0 10000 insurance
2020-1-8        #S4030050       -10000  15531.7  insurance
2020-1-8        Total: 25549.4  >>> c 15
2020-1-15       Total: 25549.4  >>> s
[0] S4030050    Balance: 15531.7
[1] 01927405    Balance: 10017.8
[2] C0628001    Balance: 0      Available credit: 30000
2020-1-15       Total: 25549.4  >>> e
Program finished.
```

**第二次运行后`example.acconut`文件内容**

```
# Runtime Example for Windows
# encoding: utf-8
a s S4030050 0.018
a s 01927405 0.018
c 5
a c C0628001 30000 0.0005 30
c 8
d 0 8200 salary
c 11
w 2 6000 buy a iPhone
c 26
d 1 10000 sell stock 1000
n
d 2 6060 repay the credit
c 8
d 0 8300 salary
c 12
w 2 2000 buy a television
n
d 2 2050 repay the credit 
# END_OF_RUN1
c 8
d 0 9000 salary
w 0 10000 insurance
c 15
```

#### Linux系统下的示例:

**第一次运行（终端Terminal）**

```
uesr@Linux:~/Documents$ ./BankAccount example.account 
Default date: 2019-11-01.

Welcome! Enter the command after ">>>".
  =======================COMMAND=======================  
	Add account(a type id [credit] rate [fee])
	  TYPE:[s]SavingsAccount -> id rate
	       [c]CreditAccount  -> id credit rate fee
	Deposit    (d account amount desc)
	Withdraw   (w account amount desc)
	Show       (s)
	Change Day (c day)
	Next Month (n)
	Query      (q yyyy-mm-dd yyyy-mm-dd)
	Exit       (e)
  =====================================================  

Commands:
2019-11-1	Total: 0	>>> a s S4030050 0.018
2019-11-1	#S4030050 is created.
2019-11-1	Total: 0	>>> a s 01927405 0.018
2019-11-1	#01927405 is created.
2019-11-1	Total: 0	>>> c 5
2019-11-5	Total: 0	>>> a c C0628001 30000 0.0005 30
2019-11-5	#C0628001 is created.
2019-11-5	Total: 0	>>> c 8
2019-11-8	Total: 0	>>> d 0 8200 salary
2019-11-8	#S4030050	8200	8200	 salary
2019-11-8	Total: 8200	>>> c 11
2019-11-11	Total: 8200	>>> w 2 6000 buy a iPhone
2019-11-11	#C0628001	-6000	-6000	 buy a iPhone
2019-11-11	Total: 2200	>>> c 26
2019-11-26	Total: 2200	>>> d 1 10000 sell stock 1000
2019-11-26	#01927405	10000	10000	 sell stock 1000
2019-11-26	Total: 12200	>>> n
2019-12-1	#C0628001	-60	-6060	Interest
2019-12-1	Total: 12140	>>> d 2 6060 repay the credit
2019-12-1	#C0628001	6060	0	 repay the credit
2019-12-1	Total: 18200	>>> c 8
2019-12-8	Total: 18200	>>> d 0 8300 salary
2019-12-8	#S4030050	8300	16500	 salary
2019-12-8	Total: 26500	>>> c 12
2019-12-12	Total: 26500	>>> w 2 2000 buy a television
2019-12-12	#C0628001	-2000	-2000	 buy a television
2019-12-12	Total: 24500	>>> n
2020-1-1	#S4030050	31.66	16531.7	Interest
2020-1-1	#01927405	17.75	10017.8	Interest
2020-1-1	#C0628001	-20	-2020	Interest
2020-1-1	#C0628001	-30	-2050	Annual fee
2020-1-1	Total: 24499.4	>>> s
[0] S4030050	Balance: 16531.7
[1] 01927405	Balance: 10017.8
[2] C0628001	Balance: -2050	Available credit: 27950
2020-1-1	Total: 24499.4	>>> d 2 2050 repay the credit
2020-1-1	#C0628001	2050	0	 repay the credit
2020-1-1	Total: 26549.4	>>> q 2019-11-01 2019-11-30
2019-11-1	#S4030050	0	0	Creation
2019-11-1	#01927405	0	0	Creation
2019-11-5	#C0628001	0	0	Creation
2019-11-8	#S4030050	8200	8200	 salary
2019-11-11	#C0628001	-6000	-6000	 buy a iPhone
2019-11-26	#01927405	10000	10000	 sell stock 1000
2020-1-1	Total: 26549.4	>>> q 2019~12~01 2019~12~31
Bad line in <stdin> q 2019~12~01 2019~12~31
Error: Invalid date
2020-1-1	Total: 26549.4	>>> e
Program finished.
```

**第一次运行后`example.acconut`文件内容**

```
# Runtime Example for Linux
# encoding: utf-8
a s S4030050 0.018
a s 01927405 0.018
c 5
a c C0628001 30000 0.0005 30
c 8
d 0 8200 salary
c 11
w 2 6000 buy a iPhone
c 26
d 1 10000 sell stock 1000
n
d 2 6060 repay the credit
c 8
d 0 8300 salary
c 12
w 2 2000 buy a television
n
d 2 2050 repay the credit
```

**第二次运行（终端Terminal）**

```
user@Linux:~/Documents$ ./BankAccount example.account 
Default date: 2019-11-01.
History:
2019-11-1	#S4030050 is created.
2019-11-1	#01927405 is created.
2019-11-5	#C0628001 is created.
2019-11-8	#S4030050	8200	8200	 salary
2019-11-11	#C0628001	-6000	-6000	 buy a iPhone
2019-11-26	#01927405	10000	10000	 sell stock 1000
2019-12-1	#C0628001	-60	-6060	Interest
2019-12-1	#C0628001	6060	0	 repay the credit
2019-12-8	#S4030050	8300	16500	 salary
2019-12-12	#C0628001	-2000	-2000	 buy a television
2020-1-1	#S4030050	31.66	16531.7	Interest
2020-1-1	#01927405	17.75	10017.8	Interest
2020-1-1	#C0628001	-20	-2020	Interest
2020-1-1	#C0628001	-30	-2050	Annual fee
2020-1-1	#C0628001	2050	0	 repay the credit

Welcome! Enter the command after ">>>".
  =======================COMMAND=======================  
	Add account(a type id [credit] rate [fee])
	  TYPE:[s]SavingsAccount -> id rate
	       [c]CreditAccount  -> id credit rate fee
	Deposit    (d account amount desc)
	Withdraw   (w account amount desc)
	Show       (s)
	Change Day (c day)
	Next Month (n)
	Query      (q yyyy-mm-dd yyyy-mm-dd)
	Exit       (e)
  =====================================================  

Commands:
2020-1-1	Total: 26549.4	>>> c 8
2020-1-8	Total: 26549.4	>>> d 0 9000 salary
2020-1-8	#S4030050	9000	25531.7	 salary
2020-1-8	Total: 35549.4	>>> w 0 10000 insurance
2020-1-8	#S4030050	-10000	15531.7	 insurance
2020-1-8	Total: 25549.4	>>> c 15
2020-1-15	Total: 25549.4	>>> s
[0] S4030050	Balance: 15531.7
[1] 01927405	Balance: 10017.8
[2] C0628001	Balance: 0	Available credit: 30000
2020-1-15	Total: 25549.4	>>> e
Program finished.
```

**第二次运行后`example.acconut`文件内容**

```
# Runtime Example for Linux
# encoding: utf-8
a s S4030050 0.018
a s 01927405 0.018
c 5
a c C0628001 30000 0.0005 30
c 8
d 0 8200 salary
c 11
w 2 6000 buy a iPhone
c 26
d 1 10000 sell stock 1000
n
d 2 6060 repay the credit
c 8
d 0 8300 salary
c 12
w 2 2000 buy a television
n
d 2 2050 repay the credit
# END_OF_RUN1
c 8
d 0 9000 salary
w 0 10000 insurance
c 15
```


