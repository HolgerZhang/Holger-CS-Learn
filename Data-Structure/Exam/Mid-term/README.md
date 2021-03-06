## 期中考试大纲

### 一、考试题型

- 选择题 15 题 x2
- 判断题 10 题 x1.5
- 填空题 10 空 x1.5
- 应用题 3 题 x6
- 算法题 8 +14

### 二、考试知识点

#### 第一章 绪论

1、数据、数据元素、数据项、数据结构（逻辑结构、存储结构）、抽象数据类型的概念。四类数据结构：集合、线性表、树、图，区分什么是逻辑结构的概念，什么是存储结构的概念，

2、算法的概念、特点，算法的时间复杂度和空间复杂度的含义和计算方法。

3、计算某一条语句执行次数或某段程序段的时间复杂度。时间复杂度计算，与后面的一些算法结合，比如在单链表中删除某个已知结点的时间复杂度。 

#### 第二章 线性表

1、线性表的概念和基本操作

2、顺序线性表下元素的存储方法，类定义和基本操作的算法和时间复杂度。插入、删除操作平均移动元素个数。顺序表下的算法。

3、单链表的结点结构、元素的存储方法，类定义和基本操作的算法和时间复杂度，插入和删除时需定位被插、删位置的前驱结点。链表下的算法。

4、循环链表、双向链表及其下的操作，与单链表下操作的不同。

5、顺序表、链表下的算法设计，一般要求直接访问表元素，不调用其他方法。

6、在不同情形下，对线性表存储结构的灵活选择，什么时候选顺序表？什么时候选单链表？循环链表？双链表？是否带头结点?

#### 第三章 栈和队列

1、栈的ADT（抽象数据类型）定义和基本操作。

2、栈的特点（后进先出表）、性质（LIFO, overflow, underflow, push, pop后栈的状态），元素依次入栈，入栈、出栈可交替进行，可能得到多个不同的序列。

3、顺序栈的类定义及实现（包括各个方法的具体实现）

4、链栈的类定义及实现（包括各个方法的具体实现）

5、栈的应用：数据逆置、进制转换、括号匹配、后缀表达式求值…

6、前缀、中缀和后缀的含义、计算及相互转换

- 中缀表示 `(A+B)*D-E/(F+A*D)+C`
- 前缀表示 `+ - * + A B D / E + F * A D C`
- 后缀表示 `A B + D * E F A D * + / - C +`

7、双栈共享空间问题

8、递归概念，递归函数由终止条件及递归部分组成；栈与函数调用和递归，用栈存放每一层函数的“调用记录”，

9、递归算法实现

10、掌握队列的抽象数据类型定义和基本操作。

11、队列的特点、性质（先进先出表,队尾入队、队头出队，元素经过队列的元素不会改变次序）

12、队列的类定义及顺序实现，顺序队列产生的假溢出问题！如何解决？

13、利用循环队列产生的问题？有哪些解决方案？ 

14、循环队列实现算法。（包括各个方法的具体实现）

15、利用栈和（或）队列的方法，编写算法。

16、链队列定义、具体实现（包括各个方法的具体实现）。

#### 第四章 字符串和数组

1、串的概念；串的基本操作，模式匹配，BF算法和KMP算法，求next值。

2、普通二维数组、基本操作： 没有插入、删除。特殊的矩阵按行存储或按列存储时，aij对应位置k的计算。注意i和j的起始位置，按行还是按列。                          

3、稀疏矩阵的存储结构，三元组表、十字链表。

#### 第五章 树和二叉树

1、树的概念和相关术语

2、树的遍历

3、树的存储

4、二叉树概念

5、一些特殊的二叉树

- 满二叉树：高度h，2h-1个结点的二叉树
- 完全二叉树：满二叉树基础上从右下方开始连续地删除若干个结点。高度h，结点个数的范围：2h-1 --- 2h-1个

6、二叉树的性质

（1）i层上最多有2i-1个结点

（2）二叉树高度为h，至多2h-1个结点，至少为h个结点(设空二叉树高度为0，仅含一个结点的二叉树高度为1)

（3）n0 = n2+1

（4）具有 n 个结点的完全二叉树的高度为  log2n +1 

（5）若对含 n 个结点的完全二叉树从上到下且从左至右进行 1 至 n 的编号，则对完全二叉树中任意一个编号为 i 的结点：(1) 若 i=1，则该结点是二叉树的根，无双亲，否则，编号为 i/2 的结点为其双亲结点；(2) 若 2i>n，则该结点无左孩子，否则，编号为 2i 的结点为其左孩子结点；(3) 若 2i+1>n，则该结点无右孩子结点，  否则，编号为2i+1 的结点为其右孩子结点。

7、求解二叉树的前序、中序、后序、层序遍历，根据2个序列构造二叉树。

8、二叉树的链式类定义及递归算法、非递归算法的实现。