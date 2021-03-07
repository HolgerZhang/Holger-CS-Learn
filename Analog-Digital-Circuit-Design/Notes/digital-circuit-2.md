# 数字电路（第二部分：时序电路）

## 触发器种类总结

### RS触发器

【重要】

- **特性方程**：<img src="https://repo.holgerbest.top/img/SQ3ACdbkvPrsVBz.png" style="zoom:80%;" />
- **驱动表**：<img src="https://repo.holgerbest.top/img/H4JihGZeCSF7uA9.png" style="zoom:0%;" />

#### 基本RS触发器

1. 有两个互补的输出端，有两个稳定的状态。
2. 有复位（Q=0）、置位（Q=1）、保持原状态三种功能。
3. R为复位输入端，S为置位输入端，可以是低电平有效，也可以是高电平有效，取决于触发器的结构。
4. 由于反馈线的存在，无论是复位还是置位，有效信号只需要作用很短的一段时间，即“一触即发”。

<img src="https://repo.holgerbest.top/img/MILSHEjW5xCdNou.png" alt="基本RS触发器功能表" style="zoom:80%;" />

#### 同步RS触发器

给触发器加一个时钟控制端CP，只有在CP端上出现时钟脉冲时，触发器的状态才能变化。

同步RS触发器的状态转换分别由R、S和CP控制，其中，R、S控制状态转换的方向；CP控制状态转换的时刻（上升沿-CP高有效 or 下降沿-CP低有效）。

问题：**空翻** 在一个时钟脉冲周期中，触发器发生多次翻转的现象

#### 主从RS触发器

<img src="https://repo.holgerbest.top/img/fhxFdobtaMp3WgD.png" alt="主从RS触发器" style="zoom:80%;" />

特点：

1. 主从触发器的翻转是在CP由1变0时刻（CP下降沿）发生的。
2. CP一旦变为0后，主触发器被封锁，其状态不再受R、S影响，因此不会有空翻现象。

### JK触发器 【重要】

- **特性方程**：<img src="https://repo.holgerbest.top/img/nyEHmc3PxdBgk5T.png" style="zoom:80%;" />
- **驱动表**：<img src="https://repo.holgerbest.top/img/LymDJ9BitqY2AFg.png" style="zoom:80%;" />

### D触发器 【重要】

**特性方程**：<img src="https://repo.holgerbest.top/img/ynDgfWOMzUcA1B5.png" style="zoom:50%;" />

### T触发器

**特性方程**：<img src="https://repo.holgerbest.top/img/EJTLOymIpvPd3hC.png" style="zoom:80%;" />

### T’触发器

**特性方程**：Q*=非Q

## 触发器的转换

将两种触发器的特性方程进行比较，得出结果。

### JK->D

<img src="https://repo.holgerbest.top/img/VRsyxivXWPcTz8A.png" alt="JK->D" style="zoom:50%;" />

### JK->T T’

<img src="https://repo.holgerbest.top/img/pPn4J1xrqW7FVCk.png" alt="JK->T T’" style="zoom:50%;" />

### D->JK

<img src="https://repo.holgerbest.top/img/PsZQeV2dIKflAMR.png" alt="D->JK" style="zoom:50%;" />

### *其他之间互转*

将状态转换图写成卡诺图的形式，然后求特性方程；将两种触发器的特性方程进行比较，得出结果。

## 时序逻辑电路

时序逻辑电路：任何一个时刻的输出状态不仅取决于当时的输入信号，还与电路的**原状态**有关。

- 输出方程（输出函数）
- 驱动方程（激励函数）（与触发器输入相连）
- 状态方程

<img src="https://repo.holgerbest.top/img/DXsKVcSwBfp6LZ3.png" style="zoom:70%;" />

根据输出信号的特点时序逻辑电路可分为米利（Mealy）型和穆尔（Moore）型。

- Mealy类型与**输入、现态**有关
- Moore类型仅于**现态**有关

### 分析 【重要】

<img src="https://repo.holgerbest.top/img/qTWh2CGmkxfSNtA.png" alt="时序电路分析" style="zoom:60%;" />

1. 写出**输出方程**，**驱动方程**；
2. 将驱动方程代入触发器的**特性方程**中，得出电路的**状态方程**；
3. 画出**状态转换表**，**状态转换图**；
4. 画出时序图（不必要）；
5. 分析**逻辑功能**。

### 同步时序逻辑电路的设计 【重要】

<img src="https://repo.holgerbest.top/img/UHjXqnFKgi4Qs36.png" style="zoom:60%;" />

1. 根据设计要求，设定状态，画出**状态转换图**；
2. **状态分配**，列状态转换编码表；
3. 画出电路的**次态卡诺图**；由触发器的驱动表得各触发器的**驱动卡诺图**，再画出**输出卡诺图**，求各触发器的**驱动方程**和**输出方程**；
4. 如果状态个数不为2^n，将驱动方程代入触发器的**特性方程**中，得出电路的**状态方程**，检查能否**自启动**（无关项能否进入有效状态）（如果不能，重新设计状态转换图）；
5. 画出逻辑电路图。

#### 建立原始状态图和状态表

1. 确定电路模型：Mealy型 or Moore型；
2. 设立初始状态；
3. 从初始状态出发，逐个增加和完善，并确定各时刻电路的输出。

- Mealy型：<img src="https://repo.holgerbest.top/img/qNSz3BuC8JHeRQp.png" alt="Mealy型" style="zoom: 50%;" />
- Moore型：<img src="https://repo.holgerbest.top/img/AFfBjaRiwuYgMGO.png" alt="Moore型" style="zoom: 50%;" />

#### 状态化简 ▲

从原始状态表中消去多余状态，得到一个既能正确地描述给定的逻辑功能，又能使所包含的状态数目达到最少的状态表，通常称这种状态表为最小化状态表。

等效状态：如果对于所有可能的输入序列，分别从Si和Sj出发，所得到的输出响应序列完全相同。等效状态具有传递性。

等效条件：满足如下两条。

- 第一，它们的输出相同。
- 第二，它们的次态属于下列情况之一：
  - a．次态相同；
  - b．次态交错或为各自的现态；
  - c．次态循环或为等效对。

最大等效类：如果一个等效类不是任何其他等效类的子集，则该等效类称为最大等效类。

**隐含表进行状态化简**

例如：

<img src="https://repo.holgerbest.top/img/HvKmNAOCESoBs5V.png" style="zoom:50%;" />

<img src="https://repo.holgerbest.top/img/IVkETAq3DLaBjCU.png" style="zoom:50%;" />

#### 状态编码

**相邻法的状态编码原则**：按从1至3的优先顺序考虑，一般将初始状态分配为“0”状态。

1. 在相同输入条件下，具有相同次态的现态应尽可能分配相邻的二进制代码；
2. 在相邻输入条件下，同一现态的次态应尽可能分配相邻的 二进制代码；
3. 输出完全相同的现态应尽可能分配相邻的二进制代码。

### 设计举例

---

设计一个串行**数据检测器**。该检测器有一个输入端X，它的功能是对输入信号进行检测。当连续输入三个1（以及三个以上1）时，该电路输出Y=1，否则输出Y=0。

（1）根据设计要求，设定状态：

- S0——初始状态或没有收到1时的状态；
- S1——收到一个1后的状态；
- S2——连续收到两个1后的状态；
- S3——连续收到三个1（以及三个以上1）后的状态。

（2）根据题意可画出原始状态图：

<img src="https://repo.holgerbest.top/img/SgboNP2rh9QvsuR.png" style="zoom:50%;" />

画出原始状态表：
<img src="https://repo.holgerbest.top/img/YsyxrOzSpqvPHtN.png" style="zoom:40%;" />

（3）状态化简。观察上图可知，S2和S3是等价状态，所以将S2和S3合并，并用S2表示，得简化状态表：<img src="https://repo.holgerbest.top/img/DbPkYuRGK8tNiX1.png" style="zoom:40%;" />

（4）状态分配。该电路有3个状态，可以用2位二进制代码组合（00、01、10、11）中的 三个代码表示。本例取S0=00、S1=01、S2=11。

（5）选择触发器：选用2个D触发器。

（6）求出状态方程、驱动方程和输出方程。

列出D触发器的驱动表、画出电路的次态和输出卡诺图。

<img src="https://repo.holgerbest.top/img/XeMNCcjb71p3sVB.png" style="zoom:60%;" />

<img src="https://repo.holgerbest.top/img/hm1wc2xptvJCzMG.png"  style="zoom:60%;" />

（7）检查能否自启动。

<img src="https://repo.holgerbest.top/img/dkJ8fBGz7rXbKTy.png" style="zoom:60%;" />

（8）画逻辑图。根据驱动方程和输出方程，画出逻辑图。

<img src="https://repo.holgerbest.top/img/wWnQA5k2YpPmfgB.png" style="zoom:60%;" />

---

## 集成电路的应用

### 计数器

4位同步二进制计数器74161 【重要】：异步清零；同步并行预置数；计数；保持。

<img src="https://repo.holgerbest.top/img/Gnu8cB7VtafWYm2.png" alt="4位同步二进制计数器74161" style="zoom:35%;" />

十进制计数器74160 【重要】：

<img src="https://repo.holgerbest.top/img/GbIAQXx91gY67sE.png" alt="十进制计数器74160" style="zoom:50%;" />

可逆计数器74191：

<img src="https://repo.holgerbest.top/img/xCq56nBE3PoibuW.png" alt="可逆计数器74191" style="zoom:35%;" />

#### 同步级联

例如：用两片4位二进制加法计数器74161采用同步级联方式构成的8位二进制同步加法计数器，模为16×16=256。

<img src="https://repo.holgerbest.top/img/tyzsLki3JlfFGeH.png"  alt="同步级联" style="zoom:60%;" />

#### 组成任意进制计数器  【重要】

例如：用集成计数器74160和与非门组成的6进制计数器。

异步清零法（RD=Q2Q1）（注意要设计到进位的下一个状态）：

<img src="https://repo.holgerbest.top/img/ywtd67b2XuCoYDH.png" alt="组成6进制计数器 异步清零" style="zoom:60%;" />

同步置数法（LD=Q2Q0）：

<img src="https://repo.holgerbest.top/img/7WqDjESVrIs5O9Q.png" alt="组成6进制计数器 同步置数" style="zoom:60%;" />

#### **组成序列信号发生器**  【重要】

例如：试用计数器74161和数据选择器设计一个01100011序列发生器。

由于**序列长度**P=8，故将74161构成模8计数器，并选用**数据选择器**74151产生所需序列，从而得电路如图所示。

<img src="https://repo.holgerbest.top/img/ub7FIh4oqfB5ijk.png" alt="01100011序列发生器" style="zoom:70%;" />

### 寄存器

寄存器：可寄存一组二进制数码的逻辑部件

74175为由边沿触发器构成的4位寄存器，为并行输入/并行输出方式。在CLK上升沿时，将D0...D3数据存入；由RD异步清零。 

<img src="https://repo.holgerbest.top/img/3ktCEScWf5Qzuh2.png" alt="74175" style="zoom:60%;" />

### 移位寄存器

移位寄存器不仅具有数码存储功能，还具有移位的功能，即在移位脉冲的作用下，依次左移或右移。

#### 右移寄存器

结构特点：左边触发器的输出端接右邻触发器的输入端。

<img src="https://repo.holgerbest.top/img/Oat9wCb53nhofRP.png" alt="右移移位寄存器" style="zoom:60%;" />

#### 左移寄存器

结构特点：右边触发器的输出端接左邻触发器的输入端。

<img src="https://repo.holgerbest.top/img/pM4eoslSK57V8fh.png" alt="左移移位寄存器" style="zoom:60%;" />

#### 双向移位寄存器74194  【重要】

<img src="https://repo.holgerbest.top/img/5Q2fyHnSIG17LsO.png" alt="双向移位寄存器74194" style="zoom:60%;" />

- DIR－数据右移串行输入端
- DIL－数据左移串行输入端
- D0...D3－数据并行输入端
- Q0...Q3－数据并行输出端
- S1、S0－工作状态控制端

#### 74194->**序列检测器**  【重要】

例如：用74194实现“1011”数据检测器

1. 待检测序列长度为4，所以选择4位移位寄存器；
2. 将待检测序列从状态输出中解读出来（组合逻辑）。

<img src="https://repo.holgerbest.top/img/2oSHQt85rsmXhVK.png" alt="" style="zoom:80%;" />

#### 移位寄存器->**移位型计数器**

- 环形计数器：N位移位寄存器可以计N个数，实现模N计数器。状态为1的输出端的序号等于计数脉冲的个数。<img src="https://repo.holgerbest.top/img/hpXoC68r92GZtTf.png" >
- 扭环形计数器：N位移位寄存器可以组成模2N的扭环形计数器，只需将末级输出反相后，接到串行输入端。<img src="https://repo.holgerbest.top/img/94xjwgiuo2HCPYO.png" alt="扭形计数器" style="zoom:80%;" />

用反馈移位寄存器实现**环行计数器**的方法：

1. 看环行计数器的状态机，是不是具有移位特性
2. 选择n位的移位寄存器，并求其反馈函数：**反馈函数的输出值其实就是次态串行输入值**；
3. 通过**卡诺图**求反馈函数表达式；
4. 电路实现。

例如：用194实现3位环行计数器

<img src="https://repo.holgerbest.top/img/dlT5KjYsufXSFA8.png" alt="3位环行计数器" style="zoom:50%;" />

该状态机的移位方向为Q2Q1Q0（右移）；其中D2为串行输入端；而Q0为串行输出端。

#### 移位寄存器->**序列发生器**  【重要】

例如：请用移位寄存器设计一个序列发生器，能够输出串行序列“101110”

步骤一：通过移位特性构建状态图（要求状态图中**不能出现重复状态**）：<img src="https://repo.holgerbest.top/img/DJrf69LWcS4eHgv.png" style="zoom:67%;"  >

步骤二：上面状态图存在移位特性，根据其移位特性求其**反馈函数**；Q3为串出；Q0为串入；反馈函数的输出即**次态的串入**。<img src="https://repo.holgerbest.top/img/Jj6evzNTsP8YlQW.png" style="zoom: 67%;"  >

<img src="https://repo.holgerbest.top/img/X1oOLcJbU5M7qiw.png" style="zoom:67%;" />