# C++实验报告

### 实验四 函数

代码文件编码：GBK (source code encoding)

本说明文档编码：GBK (this file encoding)

### 一.   实验目的

通过本次实验要达到如下目的：

1.	理解函数的基本概念

2.	掌握函数的定义、调用和声明三种流程

3.	理解引用在函数调用过程中的重要作用，掌握其具体使用方法

4.	理解并掌握函数参数默认值和函数重载的具体使用方法

### 二.	实验内容

1.	写一个判断一个整数是否是素数的函数IsPrime。在主函数中求1000以内的所有质数，每行 8个输出到屏幕上。函数原型要求为：

~~~c++
int IsPrime(int Num);
~~~

2.	编写一个函数InverseBits，将一个整数的各位数字对调。在主函数中编写测试代码，输入整数和输出新的整数。例如：输入 123，调用该函数之后，得到结果为  321。函数原型要求为：

~~~c++
int InverseBits(int Num);
~~~

3.	设计一个函数Calc，完成如下功能。

-	接受两个整数作为参数。
-	计算出最大公约数和最小公倍数。（不要在Calc函数中使用输入输出流）
-	可以在函数参数中使用引用。
-	编写主函数，测试函数功能。
-	函数原型要求为：

~~~c++
void Calc(int Num1, int Num2, int &GCD, int &LCM);
~~~

4.	编写三个重载函数printOut分别实现输出整型数、浮点型数和string字符串，输出要求如下：

-	整型数：占10列，右对齐
-	浮点型：有4位小数
-	字符串：占10列，右对齐
-	编写测试程序，测试程序中的整数、浮点数和字符串由用户输入。
