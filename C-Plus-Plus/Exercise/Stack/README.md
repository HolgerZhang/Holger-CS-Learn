# 简单的栈类模版 Stack.h

By Holger.  用数组实现，仅实现了栈的基础功能

#### 使用：

```c++
Stack<数据类型T> 栈名 ;    //默认生成空栈
```

#### 接口：

1. 数据操作

    |    方法    |           原型            |     说明     |
    | :--------: | :-----------------------: | :----------: |
    | push(item) | void push(const T &item); |     入栈     |
    |   pop()    |         T pop();          |     出栈     |
    |   get()    |  const T &get() const ;   | 访问栈顶元素 |
    |  clear()   |       void clear();       |    清空栈    |

    

2. 状态判断

    |  方法   |         原型         |     说明     |
    | :-----: | :------------------: | :----------: |
    | empty() | bool empty() const ; | 判断是否栈空 |
    | full()  | bool full() const ;  | 判断是否栈满 |

    
