#ifndef _NODE_H
#define _NODE_H

template <class T>
class LinkedList;

template <class T>                 //结点类模版
class Node{
private:
    Node<T> *nextP;                         //后继结点的地址
    friend LinkedList<T>;
public:
    T data;                                 //数据域
    Node(const T &item, Node<T> *next=0);   //构造函数
    Node();                                 //默认构造函数
    void insert(Node<T> *newP);             //在当前结点之后插入一个同类结点newP
    Node<T> *del();                         //删除当前结点之后的后继结点, 并返回删除结点的地址
    Node<T> *next();                        //获取后继结点的地址
    const Node<T> *next() const ;
};


//类实现部分
//构造函数, 初始化数据成员和指针成员
template<class T>
Node<T>::Node(const T &item, Node<T> *next): data(item), nextP(next) { }
template<class T>
Node<T>::Node():data(0), nextP(nullptr) { }


//在当前结点之后插入一个同类节点newP
template<class T>
void Node<T>::insert(Node<T> *newP) {
    newP->nextP = this->nextP;          //newP结点指针域指向当前结点的后续结点
    this->nextP = newP;                 //当前节点指针域指向newP结点
}

//删除当前结点之后的后继结点, 并返回删除结点的地址
template<class T>
Node<T> *Node<T>::del() {
    if (nextP==0)                       //如果是链表末尾返回空指针
        return nullptr;
    Node<T> *tempPtr = this->nextP;     //保存当前节点的后继结点地址
    this->nextP = tempPtr->nextP;       //将当前节点的后继节点地址改为下一个节点的后继节点地址
    return tempPtr;                     //返回删除的节点的地址
}

//获取后继结点的地址
template<class T>
Node<T> *Node<T>::next() { return nextP; }
template<class T>
const Node<T> *Node<T>::next() const { return nextP; }



#endif //_NODE_H
