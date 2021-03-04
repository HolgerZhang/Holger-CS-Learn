# C++大作业

## 任务1 kNN机器学习算法的C++实现

项目源地址：[https://gitee.com/hzhang19/Machine-Learning-k-Nearest-Neighbor](https://gitee.com/hzhang19/Machine-Learning-k-Nearest-Neighbor)

代码文件编码：UTF-8 (source code encoding)

本说明文档编码：UTF-8 (this file encoding)

### 简介

有关 kNN 和项目具体实现方法参见 `document` 目录下文件 `kNN_algorithm.pdf` 。

使用 C++ 实现了 k 近邻学习这一种最简单的机器学习算法。

要求数据集的内容格式为： `type,data1,data2,...` ，即类型在前，样本数据在后，用逗号隔开（而不是空格），一条数据占一行。在 `data` 文件夹下给出了样例数据集 `iris.data`（[鸢尾花数据集](http://archive.ics.uci.edu/ml/datasets/Iris)），可供测试使用。

实现了评价算法（评价该数据集使用 kNN 算法的预测正确性，并给出最为适合的参数 `k`）和预测算法（根据提供的数据集，预测输入的测试用例的所属类型），采用命令行参数的方式提供数据集路径等信息。



### 编译运行

依赖 cmake 编译运行，cmake 的最低版本为 3.5，源代码的组织方式详见 `CMakeLists.txt` 。

~~~shell
mkdir build
cd build
cmake ..
make
./evaluate <options>
./predict <options>
~~~

也可以使用支持 cmake 的集成开发环境（例如 CLion，Visual Studio 2019 等）编译运行。



### 运行方法

#### 1 评价算法

用于评价该数据集使用 kNN 算法的预测正确性（使用准确率 `precision` 表示），并给出最为适合的参数 `k`。

文件和与之对应参数 `k` 将保存到二进制文件所在文件夹下的 `eval.dat` 文件中（不存在将被创建）。

**使用方法**：

~~~shell
./evaluate file [range]
~~~

`file` ：数据集的路径，可以是绝对路径，也可以是相对路径（但绝对路径和不同的相对路径表示的同一个文件会被认为是不同的文件）。文件的每一行应符合 `type,data1,data2,...` ，即类型在前，样本数据在后，用逗号隔开（而不是空格）。

`range` ：（可选的，默认为 30）测试集的绝对大小，不应该大于总的数据集的一半。



#### 2 预测算法

根据提供的数据集，预测输入的测试用例的所属类型。

与文件对应参数 `k` 将从二进制文件所在文件夹下的 `eval.dat` 文件中获取（不存在将运行评价算法以计算）。

*绝对路径和不同的相对路径表示的同一个文件会被认为是不同的文件。*

**使用方法**：

~~~shell
./predict file
~~~

`file` ：数据集的路径，可以是绝对路径，也可以是相对路径。文件的每一行应符合 `type,data1,data2,...` ，即类型在前，样本数据在后，用逗号隔开（而不是空格）。



### 文件结构

~~~
.
│  CMakeLists.txt
│  CMakeSettings.json
|  LICENSE
│  README.md
│
├─data
│      iris.data
│
├─document
│      kNN_algorithm.pdf
│      Machine learning algorithm - kNN By Holger Zhang.pdf
|
└─src
    ├─evaluate
    │      eval_main.cpp
    │      eval_runner.cpp
    │      eval_runner.h
    │
    ├─predict
    │      pred_main.cpp
    │      pred_runner.cpp
    │      pred_runner.h
    │
    └─shared
            kNNHelper.cpp
            kNNHelper.h

~~~

