#ifndef _STACK_H
#define _STACK_H

#include <cassert>

//Stack类声明部分
//数据类型 T, 大小 SIZE(默认50)
template <class T,int SIZE = 50>
class Stack{    //栈类模版
private:
    T list[SIZE];   //栈
    int top;        //栈顶位置
public:
    Stack();        //构造函数
    void push(const T &item);   //入栈
    T pop();                    //出栈
    void clear();               //清空栈
    const T &get() const ;      //访问栈顶元素
    bool empty() const ;        //判断是否栈空
    bool full() const ;         //判断是否栈满
};

//Stack类实现部分
template<class T, int SIZE>     //构造函数
Stack<T, SIZE>::Stack(): top(-1) { }

template<class T, int SIZE>     //入栈
void Stack<T, SIZE>::push(const T &item) {
    assert(!full());
    list[++top] = item;
}
template<class T, int SIZE>     //出栈
T Stack<T, SIZE>::pop() {
    assert(!empty());
    return list[top--];
}
template<class T, int SIZE>     //访问栈顶元素
const T &Stack<T, SIZE>::get() const {
    assert(!empty());
    return list[top];
}

template<class T, int SIZE>     //清空栈
void Stack<T, SIZE>::clear() {
    top = -1;
}

template<class T, int SIZE>     //判断是否栈空
bool Stack<T, SIZE>::empty() const {
    return top == -1;
}
template<class T, int SIZE>     //判断是否栈满
bool Stack<T, SIZE>::full() const {
    return top == SIZE-1;
}

#endif //_STACK_H
